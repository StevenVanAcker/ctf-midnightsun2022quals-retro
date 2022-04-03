#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#define LOCKFILE "/tmp/counter-lockfile"
#define COUNTERFILE "/tmp/counter-datafile"
#define TMOUT 5
#define SLEEPTIME_US 1000
#define BUFSIZE 128

void getlock()
{
    time_t starttime = time(NULL);

    while (time(NULL) < starttime + TMOUT)
    {
        int fd = open(LOCKFILE, O_CREAT | O_EXCL);
        if (fd == -1)
        {
            if (errno != EEXIST)
            {
                fprintf(stderr, "Lock failed: %m\n");
                exit(1);
            }
            else
            {
                // fprintf(stderr, "File busy, retrying\n");
                usleep(SLEEPTIME_US);
            }
        }
        else
        {
            // we got a lock
            close(fd);
            return;
        }
    }

    fprintf(stderr, "Failed to get a lock in time\n");
    exit(1);
}

char *update_counter()
{
    char *counter = calloc(BUFSIZE, 1);
    int val = 0;
    // open counter file and read it
    FILE *inf = fopen(COUNTERFILE, "r");
    if (inf)
    {
        fread(counter, 1, BUFSIZE, inf);
        fclose(inf);
    }
    else
    {
        strcpy(counter, "0");
    }

    // increase counter and save it
    val = atoi(counter) + 1;

    sprintf(counter, "%08d", val);

    FILE *outf = fopen(COUNTERFILE, "w");
    if (!outf)
        exit(1);
    fprintf(outf, "%s", counter);
    fclose(outf);

    return counter;
}

void showcounter(char *p)
{
    while (p && *p)
    {
        printf("<img src=\"/cgi-bin/showimg.cgi?%c.gif\">", *p++);
    }
}

void releaselock()
{
    unlink(LOCKFILE);
}

void main()
{
    alarm(5);
    getlock();
    char *p = update_counter();
    releaselock();
    printf("Content-type: text/html\n\n");
    printf("<html><body background=\"/bg.jpg\" valign=center>");

    printf("<table border=0><tr>");
    printf("<td><b>You are visitor </b></td>");
    printf("<td>");
    showcounter(p);
    printf("</td></tr></table>");
    printf("<font size=-2>Best viewed in <img src=\"/ie.gif\"> Internet Explorer 4 at 1024x768 pixels.</font>");
    printf("</body></html>");
}