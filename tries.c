#include "utils.h"

int node_pool = 0;

int write_dot(FILE *f, t_trie *trie)
{
    size_t index;
    int i;

    index = (unsigned long)trie - node_pool;
    i = 0;
    while (i < ASCII_SIZE)
    {
        if (trie->childs[i] && trie->childs[i]->val)
        {
            size_t child_index = (unsigned long)trie->childs[i] - node_pool;
            fprintf(f, "    node_%zu [label=\"%c\"]\n", child_index, trie->childs[i]->val);
            fprintf(f, "    node_%zu -> node_%zu\n", index, child_index);
            if (trie->childs[i]->synergies)
            {
                t_graph *tmp = trie->childs[i]->synergies;
                while (tmp->next)
                {
                    fprintf(f, "    node_%p [label=\"%s\"]\n", tmp, tmp->champion);
                    fprintf(f, "    node_%zu -> node_%p\n", child_index, tmp);
                    tmp = tmp->next;
                }
            }
            write_dot(f, trie->childs[i]);
        }
        i++;
    }
}

t_trie *createNode(void)
{
    t_trie *new;
    int i;

    new = (t_trie *)malloc(sizeof(t_trie) * 1);
    if (!new)
    {
        printf("Could not malloc a new node");
        return (NULL);
    }
    new->is_word = 0;
    new->val = 0;
    new->synergies = NULL;
    i = 0;
    while (i < ASCII_SIZE)
    {
        new->childs[i] = NULL;
        i++;
    }
    node_pool += 1;
    return (new);
}

t_trie *search_tree_from_word(t_trie *t, char *str)
{
    t_trie *tmp;
    unsigned int i;
    int val;

    i = 0;
    tmp = t;
    while (str[i])
    {
        val = (int)(str[i] >= 'A' && str[i] <= 'Z') ? str[i] + 32 : str[i];
        if (!tmp->childs[val])
            return (NULL);
        tmp = tmp->childs[val];
        i++;
    }
    if (tmp->is_word)
        return (tmp);
    return (NULL);
}

t_trie *create_tree_from_word(t_trie *t, char *str)
{
    t_trie *tmp;
    int val;
    int i;

    i = 0;
    tmp = t;
    while (str[i])
    {
        val = (int)(str[i] >= 'A' && str[i] <= 'Z') ? str[i] + 32 : str[i];
        if (!tmp->childs[val])
            tmp->childs[val] = createNode();
        tmp = tmp->childs[val];
        tmp->val = val;
        i++;
    }
    tmp->is_word = 1;
    tmp->synergies = NULL;
    return (tmp);
}

void free_trie(t_trie *t)
{
    if (!t)
        return ;
    int i;

    i = 0;
    while (i < ASCII_SIZE)
    {
        free_trie(t->childs[i]);
        i++;
    }
    if (t->synergies)
        free_linked_list(t->synergies);
    free(t);
    t = NULL;
}

void create_digraph(t_trie *root)
{
    FILE *f;

    f = fopen("trie.dot", "w");
    if (!f)
    {
        fprintf(stderr, "Could not open the file trie.dot");
        return ;
    }
    (void)fprintf(f, "digraph Trie {\n");
    (void)fprintf(f, "    Node_%zu [label=root]\n", root - node_pool);
    (void)write_dot(f, root);
    (void)fprintf(f, "}\n");
    fclose(f);
    return ;
}