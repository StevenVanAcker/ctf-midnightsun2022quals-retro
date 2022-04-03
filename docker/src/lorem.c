#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

void ucword(char *w, int uc)
{
    printf("%c%s", uc ? toupper(w[0]) : w[0], w + 1);
}

// based on https://stackoverflow.com/questions/4286487/is-there-any-lorem-ipsum-generator-in-c
void LoremIpsum(int wordCount, int uc)
{

    char *words[] = {"lorem", "ipsum", "dolor", "sit", "amet", "consectetuer",
                     "adipiscing", "elit", "sed", "diam", "nonummy", "nibh", "euismod",
                     "tincidunt", "ut", "laoreet", "dolore", "magna", "aliquam", "erat"};

    for (int w = 0; w < wordCount; w++)
    {
        int n = random() % (sizeof(words) / sizeof(char *));
        if (w)
            printf(" ");
        ucword(words[n], uc && w == 0);
    }

    printf(". ");
}

void main()
{
    alarm(5);
    srandom(time(NULL) + getpid());
    printf("Content-type: text/html\n\n");

    printf("<html><body valign=center background=\"/bg.jpg\"><h1>Lorem Ipsum generator</h1>");
    char *qs = getenv("QUERY_STRING");
    if (!qs || !strcmp(qs, "") || strncmp(qs, "blocks=", 7))
    {
        printf("<form>"
               "<table border=0>"
               "<tr><td><label for=\"blocks\">Paragraphs</label></td><td><input type=\"text\" id=\"blocks\" name=\"blocks\" value=\"3\"></td></tr>"
               "<tr><td></td><td><input type=submit></td></tr>"
               "</table>"
               "</form>\n");
    }
    else
    {
        int paras = atoi(qs + 7);
        if (paras > 0)
        {
            for (int p = 0; p < paras; p++)
            {
                int sentences = (random() % 5) + 3;
                printf("<p>");

                for (int s = 0; s < sentences; s++)
                {
                    int words = (random() % 15) + 8;
                    if (p == 0 && s == 0)
                    {
                        printf("Lorem ipsum dolor sit amet ");
                        LoremIpsum(words, 0);
                    }
                    else
                    {
                        LoremIpsum(words, 1);
                    }
                }
                printf("</p>");
            }
        }
        printf("<br><a href=\"/cgi-bin/lorem.cgi\">Go back</a>");
    }
}