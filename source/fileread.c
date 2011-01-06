#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileread.h"


char **file_read (FILE *fp)
{
	/* copy code into array of pointer to char and return pointer to base of
	   array
	*/
   char text [MAXLINE];
   int lines = 0, i;
   int line_len;
   char **ca;

   lines = line_count (fp);
   rewind (fp);
   ca = (char **) calloc (lines + 1, sizeof (char *));
   for (i = 0; i < lines; i++)
   {
      fgets (text, MAXLINE, fp);
      line_len = strlen (text);
      text [line_len - 1] = 0;
      ca [i] = (char *) calloc (line_len, sizeof (char));
      strcpy (ca [i], text);
   }
   return ca;
}

int line_count (FILE *fp)
{
   int res = 0;
   int c;

   /* printf ("line_count\n"); */
   rewind (fp);
   while ((c = getc (fp)) != EOF)
   {
      if (c == '\n')
         res++;
   }
   return res;
}

