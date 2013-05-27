#include <iostream>
#include <string>
#include <regex.h>

#include <argtable2.h>

#include "bin2png.h"

using namespace std;

int main(int argc, char **argv) {
    /* SYNTAX 1: encode */
    struct arg_rex  *cmd1 = arg_rex1(NULL,  NULL,  "encode", NULL, REG_ICASE, NULL);
    struct arg_file *infile1 = arg_file1(NULL, NULL, NULL, "input binary file");
    struct arg_file *outfile1 = arg_file0("o", "outfile", "<outfile>", "output png file");
    struct arg_str  *password1 = arg_str0("p", "password", "<password>", "password used to encrypt output");
    struct arg_lit  *force1    = arg_lit0("f", NULL, "force encoding even when file is over 500mb");
    struct arg_end  *end1     = arg_end(20);
    void* argtable1[] = {cmd1, infile1, outfile1, password1, force1, end1};
    int nerrors1;

    /* SYNTAX 2: decode */
    struct arg_rex  *cmd2 = arg_rex1(NULL,  NULL,  "decode", NULL, REG_ICASE, NULL);
    struct arg_file *infile2 = arg_file1(NULL, NULL, NULL, "input png file");
    struct arg_file *outfile2 = arg_file0("o", "outfile", "<outfile>", "output binary file");
    struct arg_str  *password2 = arg_str0("p", "password", "<password>", "password used to decrypt output");
    struct arg_end  *end2     = arg_end(20);
    void* argtable2[] = {cmd2, infile2, outfile2, password2, end2};
    int nerrors2;

    /* SYNTAX 3: help */
    struct arg_lit  *help3    = arg_lit0("h", "help", "print this help and exit");
    struct arg_end  *end3     = arg_end(20);
    void* argtable3[] = {help3, end3};
    int nerrors3;

    const char* progname = "bin2png";
    int exitcode = 0;

    /* verify the argtable[] entries were allocated sucessfully */
    if (arg_nullcheck(argtable1) != 0 ||
        arg_nullcheck(argtable2) != 0 ||
        arg_nullcheck(argtable3) != 0) {
        /* NULL entries were detected, some allocations must have failed */
        printf("%s: insufficient memory\n",progname);
        exitcode = 1;
        goto exit;
    }

    password1->sval[0] = NULL;
    password2->sval[0] = NULL;

    /* Above we defined a separate argtable for each possible command line syntax */
    /* and here we parse each one in turn to see if any of them are successful    */
    nerrors1 = arg_parse(argc, argv, argtable1);
    nerrors2 = arg_parse(argc, argv, argtable2);
    nerrors3 = arg_parse(argc, argv, argtable3);

    /* special case: '--help' takes precedence over error reporting */
    if (help3->count > 0) {
        printf("Usage: %s", progname);
        arg_print_syntax(stdout, argtable1, "\n");
        printf("       %s", progname);
        arg_print_syntax(stdout, argtable2, "\n");
        printf("       %s", progname);
        arg_print_syntax(stdout, argtable3, "\n");
        printf("bin2png\n");
        printf("       encode\n");
        arg_print_glossary(stdout, argtable1, "            %-20s %s\n");
        printf("       decode\n");
        arg_print_glossary(stdout, argtable2, "            %-20s %s\n");
        printf("\n");
        arg_print_glossary(stdout, argtable3, "      %-20s %s\n");
        exitcode = 0;
        goto exit;
    }

    /* special case: uname with no command line options induces brief help */
    if (argc == 1) {
        printf("Try '%s --help' for more information.\n", progname);
        exitcode = 0;
        goto exit;
    }

    /* Execute the appropriate main<n> routine for the matching command line syntax */
    /* In this example program our alternate command line syntaxes are mutually     */
    /* exclusive, so we know in advance that only one of them can be successful.    */
    if (nerrors1 == 0) {
        exitcode = bin2png(infile1->filename, outfile1->filename, password1->sval[0], force1->count);
    } else if (nerrors2 == 0) {
        exitcode = png2bin(infile2->filename, outfile2->filename, password2->sval[0]);
    } else {
        /* We get here if the command line matched none of the possible syntaxes */
        if (cmd1->count > 0) {
            /* here the cmd1 argument was correct, so presume syntax 1 was intended target */ 
            arg_print_errors(stdout, end1, progname);
            printf("Usage: %s ", progname);
            arg_print_syntax(stdout, argtable1,"\n");
        } else if (cmd2->count > 0) {
            /* here the cmd2 argument was correct, so presume syntax 2 was intended target */ 
            arg_print_errors(stdout, end2, progname);
            printf("Usage: %s ", progname);
            arg_print_syntax(stdout, argtable2, "\n");
        } else {
            /* no correct cmd literals were given, so we cant presume which syntax was intended */
            printf("%s: missing <encode|decode> command.\n",progname); 
            printf("Usage: %s ", progname);  arg_print_syntax(stdout,argtable1,"\n");
            printf("       %s ", progname);  arg_print_syntax(stdout,argtable2,"\n");
            printf("       %s ", progname);  arg_print_syntax(stdout,argtable3,"\n");
            printf("\n");
            printf("Try '%s --help' for more information.\n", progname);
        }
    }

    exit:
        /* deallocate each non-null entry in each argtable */
        arg_freetable(argtable1,sizeof(argtable1)/sizeof(argtable1[0]));
        arg_freetable(argtable2,sizeof(argtable2)/sizeof(argtable2[0]));
        arg_freetable(argtable3,sizeof(argtable3)/sizeof(argtable3[0]));

        return exitcode;
}

void handle_log(const char *cmd, const char *data) {
    cout << cmd << ":" << data << endl;
}
