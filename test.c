
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void convert_to_bin(unsigned char a)
{
    unsigned char b = a;
    if (!a)
        return ;
    convert_to_bin(b / 2);
    printf("%c ", (a % 2) + '0');
}

int main()
{
    unsigned char a = 90;

    convert_to_bin(a);
    puts("");
}