#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "urldecode.h"

#define SC_PREFIX "start="
#define EC_PREFIX "end="
#define TXT_PREFIX "txt="

char *globstartcolor = "ff0000";
char *globendcolor = "ff00ff";
char *globtxt = "Hello World";

int getrgbval(char *col, int idx)
{
    char buf[3];
    col++; // get rid of the #
    buf[0] = col[idx * 2];
    buf[1] = col[idx * 2 + 1];
    buf[2] = '\0';
    return strtol(buf, NULL, 16);
}

void parse(char *qs)
{
    char *p;
    while ((p = strsep(&qs, "&")) != NULL)
    {
        if (!strncmp(p, SC_PREFIX, strlen(SC_PREFIX)))
        {
            globstartcolor = urlDecode(p + strlen(SC_PREFIX));
        }
        else if (!strncmp(p, EC_PREFIX, strlen(EC_PREFIX)))
        {
            globendcolor = urlDecode(p + strlen(EC_PREFIX));
        }
        else if (!strncmp(p, TXT_PREFIX, strlen(TXT_PREFIX)))
        {
            globtxt = urlDecode(p + strlen(TXT_PREFIX));
        }
    }
}

char *coloredletter(char *txt, char *startcolor, char *endcolor, int index)
{
    int ar, ag, ab;
    int br, bg, bb;
    int len = strlen(txt);
    static char buf[100];

    ar = getrgbval(startcolor, 0);
    ag = getrgbval(startcolor, 1);
    ab = getrgbval(startcolor, 2);
    br = getrgbval(endcolor, 0);
    bg = getrgbval(endcolor, 1);
    bb = getrgbval(endcolor, 2);

    float ratio = (float)index / (float)(len - 1);

    int r = ar + (((float)(br - ar)) * ratio);
    int g = ag + (((float)(bg - ag)) * ratio);
    int b = ab + (((float)(bb - ab)) * ratio);

    snprintf(buf, sizeof(buf), "<font color=\"#%02x%02x%02x\">%c</font>", r, g, b, txt[index]);
    return buf;
}

void main()
{
    alarm(5);
    printf("Content-type: text/html\n\n");

    printf("<html><body background=\"/bg.jpg\">\n");
    printf("<h1>Colorize text</h1>");
    char *qs = getenv("QUERY_STRING");
    if (!qs || !strcmp(qs, ""))
    {
        printf("<form>"
               "<table border=0>"
               "<tr><td><label for=\"start\">Start color</label></td><td><input type=\"color\" id=\"start\" name=\"start\" value=\"#ff0000\"></td></tr>"
               "<tr><td><label for=\"end\">End color</label></td><td><input type=\"color\" id=\"end\" name=\"end\" value=\"#00ff00\"></td></tr>"
               "<tr><td><label for=\"txt\">Text</label></td><td><input type=\"text\" size=30 id=\"txt\" name=\"txt\" value=\"Hello Beautiful Colored World\"></td></tr>"
               "<tr><td></td><td><input type=submit></td></tr>"
               "</table>"
               "</form>\n");
    }
    else
    {
        parse(qs);
        int txtlen = strlen(globtxt);
        printf("<center>");

        for (int i = 0; i < txtlen; i++)
        {
            printf("%s", coloredletter(globtxt, globstartcolor, globendcolor, i));
        }

        printf("</center>");

        printf("<br><br><br><a href=\"/cgi-bin/color.cgi\">Go back</a>");
    }
    printf("</body></html>\n");
}
