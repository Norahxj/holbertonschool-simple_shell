#include "shell.h"

#define TOK_BUFSIZE 64

static int is_delim(char c)
{
return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\a');
}

static void free_tokens(char **tokens)
{
int i;

if (!tokens)
return;

for (i = 0; tokens[i]; i++)
free(tokens[i]);

free(tokens);
}

char **split_line(char *line)
{
int bufsize = TOK_BUFSIZE;
int pos = 0;
int i = 0, start, len, k;
char **tokens;

if (!line)
return (NULL);

tokens = malloc(bufsize * sizeof(char *));
if (!tokens)
return (NULL);

while (line[i] != '\0')
{
while (line[i] != '\0' && is_delim(line[i]))
i++;

if (line[i] == '\0')
break;

start = i;

while (line[i] != '\0' && !is_delim(line[i]))
i++;

len = i - start;

tokens[pos] = malloc((len + 1) * sizeof(char));
if (!tokens[pos])
{
free_tokens(tokens);
return (NULL);
}

for (k = 0; k < len; k++)
tokens[pos][k] = line[start + k];
tokens[pos][k] = '\0';

pos++;

if (pos >= bufsize)
{
char **tmp;

bufsize += TOK_BUFSIZE;
tmp = realloc(tokens, bufsize * sizeof(char *));
if (!tmp)
{
free_tokens(tokens);
return (NULL);
}
tokens = tmp;
}
}

tokens[pos] = NULL;
return (tokens);
}

