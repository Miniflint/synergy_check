#include "utils.h"

void free_linked_list(t_graph *ptr)
{
    if (!ptr)
        return ;
    free_linked_list(ptr->next);
    free(ptr);
    ptr = NULL; 
}

void my_strcpy(char *dest, char *src)
{
    unsigned short i;

    i = 0;
    while (src[i])
    {
        dest[i] = (src[i] >= 'A' && src[i] <= 'Z') ? src[i] + 32 : src[i];
        i++;
    }
    dest[i] = 0;
}

unsigned int my_strlen(char *str)
{
    unsigned int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int my_strlen_delim(char *str, char delim)
{
    int i;

    i = 0;
    while (str[i] && str[i] != delim)
    {
        i++;
    }
    return (i);
}

char *my_strldup(char *s2, int len)
{
    unsigned short i;
    char *s1;

    i = 0;
    s1 = (char *)malloc(sizeof(char) * (len + 1));
    while (s2[i] && i < len)
    {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = 0;
    return (s1);
}

void rm_bn(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\n' || str[i] == '\r')
        {
            str[i] = 0;
            return ;
        }
        i++;
    }
}


void my_memset(char *str, int c, size_t n)
{
    int i;

    i = 0;
    while (i < n)
    {
        str[i] = c;
        i++;
    }
    str[i] = 0;
}