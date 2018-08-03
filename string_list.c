#include <stdio.h>
#include <stdlib.h>
#include <string_list.h>

struct str_list_s
{
    char **list;
    void (*free)(void);
    void (*reset_index)(void);
    char *(*next)


} ;

str_list_t *create_list(void)
{
    str_list_t *slist = calloc(sizeof(slist),1);
    return slist;
}

