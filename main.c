#include "utils.h"
#include <string.h>

void get_synergies(t_trie *t, char *champ)
{
    t_trie *end_ptr;
    t_graph *list;

    if (!champ)
        return ;
    end_ptr = search_tree_from_word(t, champ);
    if (!end_ptr)
    {
        (void)fprintf(stderr, "%s does not exist\n", champ);
        return ;
    }
    list = end_ptr->synergies;
    printf("%s:\n", champ);
    while (list)
    {
        printf("\t%s\n", list->champion);
        list = list->next;
    }
}

int makeSynergie(t_trie *end_champ_ptr, char *syn_name)
{
    t_graph *graphSyn;
    t_graph *syn_ptr;

    graphSyn = (t_graph *)malloc(sizeof(t_graph) * 1);
    if (!graphSyn)
        return (1);
    my_strcpy(graphSyn->champion, syn_name);
    graphSyn->next = NULL;
    syn_ptr = end_champ_ptr->synergies;
    if (!syn_ptr)
        end_champ_ptr->synergies = graphSyn;
    else
    {
        while (syn_ptr->next)
        {
            syn_ptr = syn_ptr->next;
        }
        syn_ptr->next = graphSyn;
    }
    return (0);
}

int get_file_size(char *filename)
{
    FILE *f;
    int size;

    f = fopen(filename, "r");
    if (!f)
    {
        (void)fprintf(stderr, "Could not open the file: %s\n", filename);
        return (1);
    }
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fseek(f, 0, SEEK_SET);
    fclose(f);
    return(size);
}

int read_file(char *filename, t_trie *t)
{
    FILE    *file;
    char    str[get_file_size(filename)];
    char    *tmp;
    int     len;
    char    *champ;
    char    *synergie;
    t_trie  *tmpChamp;
    t_trie  *tmpSyn;

    file = fopen(filename, "r");
    if (!file)
        return (1);
    tmp = str;
    while (fgets(tmp, ((CHAMP_MAX_NAME * 10)), file))
    {
        rm_bn(tmp);
        len = my_strlen_delim(tmp, ':');
        champ = my_strldup(tmp, len);
        if (!champ)
            return (1);
        tmpChamp = search_tree_from_word(t, champ);
        if (!tmpChamp)
            tmpChamp = create_tree_from_word(t, champ);
        while (*tmp)
        {
            tmp += len;
            while (*tmp && (*tmp == ' ' || *tmp == ':' || *tmp == ','))
                tmp++;
            len = my_strlen_delim(tmp, ',');
            if (len > 0)
            {
                synergie = my_strldup(tmp, len);
                if (!synergie)
                    return (1);
                tmpSyn = search_tree_from_word(t, synergie);
                if (!tmpSyn)
                    tmpSyn = create_tree_from_word(t, synergie);
                if (makeSynergie(tmpChamp, synergie))
                    return (1);
                if(makeSynergie(tmpSyn, champ))
                    return (1);
                free(synergie);
                synergie = NULL;
            }
        }
        free(champ);
        champ = NULL;
    }
    fclose(file);
    return (0);
}

int main(int argc, char *argv[])
{
    t_trie *root;
    int ret_parse;
    char *champ;
    
    root = createNode();
    champ = (argc > 1) ? argv[1] : NULL;
    ret_parse = read_file("outfiles/synergies.txt", root);
    if (ret_parse == 0)
    {
        get_synergies(root, champ);
        create_digraph(root);
    }
    free_trie(root);
    return (0);
}
