#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

//#define JOKEFILE "../data/jokes.txt"
#define JOKEFILE "/usr/local/apache2/data/jokes.txt"
#define MAXSIZE (1024 * 1024)

void printrndline(char *fn)
{
    FILE *inf = fopen(fn, "r");
    char *out = calloc(1, MAXSIZE);

    if (!inf)
        exit(1);
    if (!out)
        exit(2);

    int readb = fread(out, 1, MAXSIZE, inf);
    if (readb < 0)
        exit(3);

    out[readb] = '\0';

    // now take a random number in this range
    int rndnum = random() % readb;

    // go to this offset and find the end of the line
    char *p = &out[rndnum];
    p = strchr(p, '\n');

    if (!p || ((p - out) == readb - 1))
    {
        printf("Reached the end\n");
        p = out;
    }
    else
    {
        p++;
    }

    while (p && *p != '\n')
        putc(*p++, stdout);
    printf("\n");
}

void main()
{
    alarm(5);
    srandom(time(NULL) + getpid());
    printf("Content-type: text/html\n\n");

    printf("<html><body valign=center background=\"/bg.jpg\"><font size=+2><b>Joke of the day</b></font><br><font size=+1>");
    printrndline(JOKEFILE);
    printf("</font></body></html>");
}