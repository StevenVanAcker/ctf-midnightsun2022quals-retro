#include <stdio.h>

void main()
{
    FILE *inf = fopen("/flag.txt", "r");
    int c = 0;

    while (0 <= (c = fgetc(inf)))
    {
        printf("%c", c);
    }
    fclose(inf);
}