#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "urldecode.h"

#define ENVVAR "DEBUG"
#define PREFIX_ADJECTIVE "adj="
#define PREFIX_NOUN "noun="
#define PREFIX_ANIMAL "animal="
#define PREFIX_NOISE "noise="
#define PREFIX_FIX "fix"

char *globtemplateorig =
    "<b>%s</b> Macdonald had a <b>%s</b>, E-I-E-I-O<br>"
    "and on that <b>%s</b> he had a <b>%s</b>, E-I-E-I-O<br>"
    "with a <b>%s</b> <b>%s</b> here<br>"
    "and a <b>%s</b> <b>%s</b> there,<br>"
    "here a <b>%s</b>, there a <b>%s</b>,<br>"
    "everywhere a <b>%s</b> <b>%s</b>,<br>"
    "<b>%s</b> Macdonald had a <b>%s</b>, E-I-E-I-O.<br>";

char *globadj = "Old", *globnoun = "Farm", *globanimal = "Cow", *globnoise = "Moo";

void showmadlib(char *qs)
{
    char template[512];
    char *p;

    strcpy(template, globtemplateorig);

    while ((p = strsep(&qs, "&")) != NULL)
    {
        if (!strncmp(p, PREFIX_ADJECTIVE, strlen(PREFIX_ADJECTIVE)))
        {
            globadj = urlDecode(p + strlen(PREFIX_ADJECTIVE));
        }
        else if (!strncmp(p, PREFIX_NOUN, strlen(PREFIX_NOUN)))
        {
            globnoun = urlDecode(p + strlen(PREFIX_NOUN));
        }
        else if (!strncmp(p, PREFIX_ANIMAL, strlen(PREFIX_ANIMAL)))
        {
            globanimal = urlDecode(p + strlen(PREFIX_ANIMAL));
        }
        else if (!strncmp(p, PREFIX_NOISE, strlen(PREFIX_NOISE)))
        {
            globnoise = urlDecode(p + strlen(PREFIX_NOISE));
        }
        else if (!strncmp(p, PREFIX_FIX, strlen(PREFIX_FIX)))
        {
            char *paddr = p + strlen(PREFIX_FIX);
            char *pval = strchr(paddr, '=');
            if (pval)
            {
                *pval++ = '\0';
                paddr = urlDecode(paddr);
                pval = urlDecode(pval);

                int offset = atoi(paddr);
                char val = atoi(pval) & 0xff;
                template[offset] = val;
            }
        }
    }

    printf(template, globadj, globnoun,
           globnoun, globanimal,
           globnoise, globnoise, globnoise, globnoise, globnoise, globnoise, globnoise, globnoise,
           globadj, globnoun);
}

void main()
{
    alarm(5);
    printf("Content-type: text/html\n\n");

    printf("<html><body background=\"/bg.jpg\">\n");
    printf("<h1>Mad Lib generator</h1>");
    char *qs = getenv("QUERY_STRING");
    if (!qs || !strcmp(qs, ""))
    {
        printf("<form>"
               "<table border=0>"
               "<tr><td><label for=\"adj\">Adjective</label></td><td><input type=\"text\" id=\"adj\" name=\"adj\" value=\"Old\"></td></tr>"
               "<tr><td><label for=\"noun\">Noun</label></td><td><input type=\"text\" id=\"noun\" name=\"noun\" value=\"Farm\"></td></tr>"
               "<tr><td><label for=\"animal\">Animal</label></td><td><input type=\"text\" id=\"animal\" name=\"animal\" value=\"Cow\"></td></tr>"
               "<tr><td><label for=\"noise\">Noise</label></td><td><input type=\"text\" id=\"noise\" name=\"noise\" value=\"Moo\"></td></tr>"
               "<tr><td></td><td><input type=submit></td></tr>"
               "</table>"
               "</form>\n");
    }
    else
    {
        showmadlib(qs);
        printf("<a href=\"/cgi-bin/madlib.cgi\">Go back</a>");
    }

    if (getenv(ENVVAR))
    {
        char cmd[100];
        snprintf(cmd, sizeof(cmd), "echo \"[DBG] %s\" >> /opt/logfile", getenv(ENVVAR));
        system(cmd);
        printf("<!-- [DEBUG ACTIVE] -->\n");
    }
}
