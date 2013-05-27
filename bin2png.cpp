#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>

#include <png++/png.hpp>
#include <png++/image.hpp>
#include <png++/rgb_pixel.hpp>

#ifdef ANDROID
#include "android_wrapper.h"
#else
#include "linux_wrapper.h"
#endif

#include "misc.h"


using namespace std;

int bin2png(const char **infile, const char **outfile, const char *password, int force) {
    handle_log("bin2png_start", *(infile));

    bool has_password = false;
    double password_number = 1;
    if (password != NULL) {
        has_password = true;
        for(int d = 0; d < strlen(password); d++) {
            password_number += password[d] * (255 ^ (strlen(password) - d - 1));
        }
        cout << password_number << endl;
    }

    ifstream binfile (*(infile), ios::in | ios::binary);
    if (!binfile.is_open()) {
        handle_log("infile_fail", *(infile));
        return 0;
    }

    binfile.seekg (0, ios::end);
    long length = binfile.tellg();
    binfile.seekg (0, ios::beg);

    // File is larger than 500mb
    if (length > 536870912 && force <= 0) {
        handle_log("file_size", "force");
        return 0;
    }

    int dimension = sqrt((length + 2) / 4) + 1;

    cout << length << endl;

    png::image<png::rgba_pixel> image(dimension, dimension);

    // File size
    image[0][0].red = (length) & 0xFF;
    image[0][0].green = (length >> 8) & 0xFF;
    image[0][0].blue = (length >> 16) & 0xFF;
    image[0][0].alpha = (length >> 24) & 0xFF;

    // Has password
    image[0][1].red = has_password;

    int x = 2;
    int y = 0;

    char src[4];
    char dest[4];
    char *buff = src;
    for (int offset = 0; offset < length; offset += 4) {
        buff = src;
        binfile.read(src, 4);

        if (offset >= length - 4) {
            for (int i = length % 4; i < 4; i++) {
                buff[i] = 0;
            }
        }  

        if (has_password) {
            swap_chars(src, dest, hash(password_number, offset / 4));
            buff = dest;
        }

        image[y][x].red = (unsigned char)buff[0];
        image[y][x].green = (unsigned char)buff[1];
        image[y][x].blue = (unsigned char)buff[2];
        image[y][x].alpha = (unsigned char)buff[3];

        x++;
        if (x >= dimension) {
            x = 0;
            y++;
        }
    }

    image.write(*(outfile));
    binfile.close();

    return 1;
}

int png2bin(const char **infile, const char **outfile, const char *password) {
    handle_log("png2bin_start", *(infile));

    bool has_password = false;
    double password_number = 1;
    if (password != NULL) {
        has_password = true;
        for(int d = 0; d < strlen(password); d++) {
            password_number += password[d] * (255 ^ (strlen(password) - d - 1));
        }
    }

    png::image<png::rgba_pixel> image(*(infile), png::require_color_space<png::rgba_pixel>());

    int dimension = image.get_width();

    // File size
    int red = image[0][0].red;
    int green = image[0][0].green << 8;
    int blue = image[0][0].blue << 16;
    int alpha = image[0][0].alpha << 24;
    long length = red | green | blue | alpha;

    // Has password
    if (image[0][1].red && !has_password) {
        handle_log("password_missing", "q");
    }

    cout << length << endl;

    ofstream binfile (*(outfile), ios::out | ios::binary);
    if (!binfile.is_open()) {
        handle_log("outfile_fail", *(outfile));
        return 0;
    }

    int x = 2;
    int y = 0;

    char src[4];
    char dest[4];
    char *buff = src;
    for (int offset = 0; offset < length; offset += 4) {
        buff = src;
        src[0] = image[y][x].red;
        src[1] = image[y][x].green;
        src[2] = image[y][x].blue;
        src[3] = image[y][x].alpha;

        if (has_password) {
            unswap_chars(src, dest, hash(password_number, offset / 4));
            buff = dest;
        }

        if (offset >= length - 4) {
            binfile.write(buff, length % 4);
        } else {
            binfile.write(buff, 4);
        }

        x++;
        if (x >= dimension) {
            x = 0;
            y++;
        }
        
    }

    binfile.close();

    return 1;
}
