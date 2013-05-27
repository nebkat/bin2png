#ifndef MISC_H
#define MISC_H

int hash(int a, int b);

char *swap_chars(char old_buff[4], char new_buff[4], int hash);
char *unswap_chars(char old_buff[4], char new_buff[4], int hash);

#endif
