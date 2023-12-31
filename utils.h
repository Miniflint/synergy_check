#ifndef UTILS_H
# define UTILS_H

#define CHAMP_MAX_NAME 50
#define ALPHABET 26
#define ASCII_SIZE 127

#include <stdlib.h>
#include <stdio.h>

typedef struct S_Graph
{
    char            champion[CHAMP_MAX_NAME + 1];
    struct S_Graph  *next;
}   t_graph;

typedef struct S_Trie
{
    int is_word;
    char val;
    t_graph *synergies;
    struct S_Trie *childs[ASCII_SIZE + 1];
}   t_trie;

/* QUICK FUNCTIONS */
void    rm_bn(char *str);
unsigned int    my_strlen(char *str);
void    free_linked_list(t_graph *ptr);
char    *my_strldup(char *s2, int len);
void    my_strcpy(char *dest, char *src);
int     my_strchr(char *src, char *needle);
int     my_strlen_delim(char *str, char delim);
void    my_memset(char *str, int c, size_t n);

/* TRIE */
t_trie *createNode(void);
t_trie *create_tree_from_word(t_trie *t, char *str);
t_trie *search_tree_from_word(t_trie *t, char *str);

/* TRIE UTILS */
void create_digraph(t_trie *root);
void free_trie(t_trie *t);

#endif