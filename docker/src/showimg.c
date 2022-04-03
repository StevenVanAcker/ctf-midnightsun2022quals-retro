#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#define BASEPATH "/usr/local/apache2/data/"
#define SUFFIX ".gif"
#define BUFSIZE (1024 * 1024 * 2)
#define PATHSIZE 128
void dumpfile(char *p)
{
    char buffer[BUFSIZE];
    char path[PATHSIZE];

    {
        int slen = strlen(p);
        char *bla = p + slen - strlen(SUFFIX);
        if (strcmp(bla, SUFFIX))
        {
            printf("ERROR: must be a " SUFFIX " file\n");
            exit(1);
        }
    }

    snprintf(path, sizeof(path), "%s/%s", BASEPATH, p);

    FILE *inf = fopen(path, "r");

    if (!inf)
    {
        printf("ERROR: file does not exist\n");
        exit(1);
    }

    int dlen = fread(buffer, 1, BUFSIZE, inf);
    fwrite(buffer, 1, dlen, stdout);
}

void main()
{
    alarm(5);
    printf("Content-type: image/gif\n\n");

    char *qs = getenv("QUERY_STRING");
    if (!qs)
        qs = "";

    dumpfile(qs);
}