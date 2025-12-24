#include "shell.h"

int _strcmp(const char *s1, const char *s2)
{
while (*s1 && (*s1 == *s2))
{
s1++;
s2++;
}
return ((unsigned char)*s1 - (unsigned char)*s2);
}

int _strlen(const char *s)
{
int n = 0;

if (!s)
return (0);

while (s[n])
n++;
return (n);
}

char *_strdup(const char *s)
{
int len, i;
char *p;

if (!s)
return (NULL);

len = _strlen(s);
p = malloc(len + 1);
if (!p)
return (NULL);

for (i = 0; i < len; i++)
p[i] = s[i];
p[i] = '\0';

return (p);
}

char *_strchr(const char *s, char c)
{
if (!s)
return (NULL);

while (*s)
{
if (*s == c)
return ((char *)s);
s++;
}
if (c == '\0')
return ((char *)s);

return (NULL);
}

