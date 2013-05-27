#ifndef BIN2PNG_H
#define BIN2PNG_H

int bin2png(const char **infile, const char **outfile, const char *password, int force);
int png2bin(const char **infile, const char **outfile, const char *password);

#endif
