#include <iostream>

int hash(int a, int b) {
   a = (a+0x7ed55d16) + (a<<12);
   a = (a^0xc761c23c) ^ (a>>19);
   a = (a+0x165667b1) + (a<<5);
   a = (a+0xd3a2646c) ^ (a<<9);
   a = (a+0xfd7046c5) + (a<<3);
   a = (a^0xb55a4f09) ^ (a>>16);
 
   b = (b+0x7ed55d16) + (b<<12);
   b = (b^0xc761c23c) ^ (b>>19);
   b = (b+0x165667b1) + (b<<5);
   b = (b+0xd3a2646c) ^ (b<<9);
   b = (b+0xfd7046c5) + (b<<3);
   b = (b^0xb55a4f09) ^ (b>>16);
 
   return a^b;
}

void swap_chars(char old_buff[4], char new_buff[4], int hash) {
    hash %= 24;

    switch (hash) {
        case 1:
            new_buff[0] = old_buff[0];
            new_buff[1] = old_buff[1];
            new_buff[2] = old_buff[2];
            new_buff[3] = old_buff[3];
            break;
        case 2:
            new_buff[0] = old_buff[0];
            new_buff[1] = old_buff[1];
            new_buff[2] = old_buff[3];
            new_buff[3] = old_buff[2];
            break;
        case 3:
            new_buff[0] = old_buff[0];
            new_buff[1] = old_buff[2];
            new_buff[2] = old_buff[1];
            new_buff[3] = old_buff[3];
            break;
        case 4:
            new_buff[0] = old_buff[0];
            new_buff[1] = old_buff[2];
            new_buff[2] = old_buff[3];
            new_buff[3] = old_buff[1];
            break;
        case 5:
            new_buff[0] = old_buff[0];
            new_buff[1] = old_buff[3];
            new_buff[2] = old_buff[1];
            new_buff[3] = old_buff[2];
            break;
        case 6:
            new_buff[0] = old_buff[0];
            new_buff[1] = old_buff[3];
            new_buff[2] = old_buff[2];
            new_buff[3] = old_buff[1];
            break;
        case 7:
            new_buff[0] = old_buff[1];
            new_buff[1] = old_buff[0];
            new_buff[2] = old_buff[2];
            new_buff[3] = old_buff[3];
            break;
        case 8:
            new_buff[0] = old_buff[1];
            new_buff[1] = old_buff[0];
            new_buff[2] = old_buff[3];
            new_buff[3] = old_buff[2];
            break;
        case 9:
            new_buff[0] = old_buff[1];
            new_buff[1] = old_buff[2];
            new_buff[2] = old_buff[0];
            new_buff[3] = old_buff[3];
            break;
        case 10:
            new_buff[0] = old_buff[1];
            new_buff[1] = old_buff[2];
            new_buff[2] = old_buff[3];
            new_buff[3] = old_buff[0];
            break;
        case 11:
            new_buff[0] = old_buff[1];
            new_buff[1] = old_buff[3];
            new_buff[2] = old_buff[0];
            new_buff[3] = old_buff[2];
            break;
        case 12:
            new_buff[0] = old_buff[1];
            new_buff[1] = old_buff[3];
            new_buff[2] = old_buff[2];
            new_buff[3] = old_buff[0];
            break;
        case 13:
            new_buff[0] = old_buff[2];
            new_buff[1] = old_buff[0];
            new_buff[2] = old_buff[1];
            new_buff[3] = old_buff[3];
            break;
        case 14:
            new_buff[0] = old_buff[2];
            new_buff[1] = old_buff[0];
            new_buff[2] = old_buff[3];
            new_buff[3] = old_buff[1];
            break;
        case 15:
            new_buff[0] = old_buff[2];
            new_buff[1] = old_buff[1];
            new_buff[2] = old_buff[0];
            new_buff[3] = old_buff[3];
            break;
        case 16:
            new_buff[0] = old_buff[2];
            new_buff[1] = old_buff[1];
            new_buff[2] = old_buff[3];
            new_buff[3] = old_buff[0];
            break;
        case 17:
            new_buff[0] = old_buff[2];
            new_buff[1] = old_buff[3];
            new_buff[2] = old_buff[0];
            new_buff[3] = old_buff[1];
            break;
        case 18:
            new_buff[0] = old_buff[2];
            new_buff[1] = old_buff[3];
            new_buff[2] = old_buff[1];
            new_buff[3] = old_buff[0];
            break;
        case 19:
            new_buff[0] = old_buff[3];
            new_buff[1] = old_buff[0];
            new_buff[2] = old_buff[1];
            new_buff[3] = old_buff[2];
            break;
        case 20:
            new_buff[0] = old_buff[3];
            new_buff[1] = old_buff[0];
            new_buff[2] = old_buff[2];
            new_buff[3] = old_buff[1];
            break;
        case 21:
            new_buff[0] = old_buff[3];
            new_buff[1] = old_buff[1];
            new_buff[2] = old_buff[0];
            new_buff[3] = old_buff[2];
            break;
        case 22:
            new_buff[0] = old_buff[3];
            new_buff[1] = old_buff[1];
            new_buff[2] = old_buff[2];
            new_buff[3] = old_buff[0];
            break;
        case 23:
            new_buff[0] = old_buff[3];
            new_buff[1] = old_buff[2];
            new_buff[2] = old_buff[0];
            new_buff[3] = old_buff[1];
            break;
        case 24:
            new_buff[0] = old_buff[3];
            new_buff[1] = old_buff[2];
            new_buff[2] = old_buff[1];
            new_buff[3] = old_buff[0];
            break;
        default:
            new_buff[0] = old_buff[0];
            new_buff[1] = old_buff[1];
            new_buff[2] = old_buff[2];
            new_buff[3] = old_buff[3];
            break;
    }
}

void unswap_chars(char old_buff[4], char new_buff[4], int hash) {
    hash %= 24;

    switch (hash) {
        case 1:
            new_buff[0] = old_buff[0];
            new_buff[1] = old_buff[1];
            new_buff[2] = old_buff[2];
            new_buff[3] = old_buff[3];
            break;
        case 2:
            new_buff[0] = old_buff[0];
            new_buff[1] = old_buff[1];
            new_buff[3] = old_buff[2];
            new_buff[2] = old_buff[3];
            break;
        case 3:
            new_buff[0] = old_buff[0];
            new_buff[2] = old_buff[1];
            new_buff[1] = old_buff[2];
            new_buff[3] = old_buff[3];
            break;
        case 4:
            new_buff[0] = old_buff[0];
            new_buff[2] = old_buff[1];
            new_buff[3] = old_buff[2];
            new_buff[1] = old_buff[3];
            break;
        case 5:
            new_buff[0] = old_buff[0];
            new_buff[3] = old_buff[1];
            new_buff[1] = old_buff[2];
            new_buff[2] = old_buff[3];
            break;
        case 6:
            new_buff[0] = old_buff[0];
            new_buff[3] = old_buff[1];
            new_buff[2] = old_buff[2];
            new_buff[1] = old_buff[3];
            break;
        case 7:
            new_buff[1] = old_buff[0];
            new_buff[0] = old_buff[1];
            new_buff[2] = old_buff[2];
            new_buff[3] = old_buff[3];
            break;
        case 8:
            new_buff[1] = old_buff[0];
            new_buff[0] = old_buff[1];
            new_buff[3] = old_buff[2];
            new_buff[2] = old_buff[3];
            break;
        case 9:
            new_buff[1] = old_buff[0];
            new_buff[2] = old_buff[1];
            new_buff[0] = old_buff[2];
            new_buff[3] = old_buff[3];
            break;
        case 10:
            new_buff[1] = old_buff[0];
            new_buff[2] = old_buff[1];
            new_buff[3] = old_buff[2];
            new_buff[0] = old_buff[3];
            break;
        case 11:
            new_buff[1] = old_buff[0];
            new_buff[3] = old_buff[1];
            new_buff[0] = old_buff[2];
            new_buff[2] = old_buff[3];
            break;
        case 12:
            new_buff[1] = old_buff[0];
            new_buff[3] = old_buff[1];
            new_buff[2] = old_buff[2];
            new_buff[0] = old_buff[3];
            break;
        case 13:
            new_buff[2] = old_buff[0];
            new_buff[0] = old_buff[1];
            new_buff[1] = old_buff[2];
            new_buff[3] = old_buff[3];
            break;
        case 14:
            new_buff[2] = old_buff[0];
            new_buff[0] = old_buff[1];
            new_buff[3] = old_buff[2];
            new_buff[1] = old_buff[3];
            break;
        case 15:
            new_buff[2] = old_buff[0];
            new_buff[1] = old_buff[1];
            new_buff[0] = old_buff[2];
            new_buff[3] = old_buff[3];
            break;
        case 16:
            new_buff[2] = old_buff[0];
            new_buff[1] = old_buff[1];
            new_buff[3] = old_buff[2];
            new_buff[0] = old_buff[3];
            break;
        case 17:
            new_buff[2] = old_buff[0];
            new_buff[3] = old_buff[1];
            new_buff[0] = old_buff[2];
            new_buff[1] = old_buff[3];
            break;
        case 18:
            new_buff[2] = old_buff[0];
            new_buff[3] = old_buff[1];
            new_buff[1] = old_buff[2];
            new_buff[0] = old_buff[3];
            break;
        case 19:
            new_buff[3] = old_buff[0];
            new_buff[0] = old_buff[1];
            new_buff[1] = old_buff[2];
            new_buff[2] = old_buff[3];
            break;
        case 20:
            new_buff[3] = old_buff[0];
            new_buff[0] = old_buff[1];
            new_buff[2] = old_buff[2];
            new_buff[1] = old_buff[3];
            break;
        case 21:
            new_buff[3] = old_buff[0];
            new_buff[1] = old_buff[1];
            new_buff[0] = old_buff[2];
            new_buff[2] = old_buff[3];
            break;
        case 22:
            new_buff[3] = old_buff[0];
            new_buff[1] = old_buff[1];
            new_buff[2] = old_buff[2];
            new_buff[0] = old_buff[3];
            break;
        case 23:
            new_buff[3] = old_buff[0];
            new_buff[2] = old_buff[1];
            new_buff[0] = old_buff[2];
            new_buff[1] = old_buff[3];
            break;
        case 24:
            new_buff[3] = old_buff[0];
            new_buff[2] = old_buff[1];
            new_buff[1] = old_buff[2];
            new_buff[0] = old_buff[3];
            break;
        default:
            new_buff[0] = old_buff[0];
            new_buff[1] = old_buff[1];
            new_buff[2] = old_buff[2];
            new_buff[3] = old_buff[3];
            break;
    }
}
