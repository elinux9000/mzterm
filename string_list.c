#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string_list.h>

//str_list_imp_s implements the list.  It "inherits" from str_list_s
struct str_list_imp_s
{
    struct str_list_s parent;
    char **arr;
    size_t size;
    size_t index;
};
typedef struct str_list_imp_s str_list_imp_t;


int compare (const void * a, const void * b)
{
    const char *name1_ = *(const char **)a;
    const char *name2_ = *(const char **)b;
    return strcmp(name1_, name2_);
}

static void sort(str_list_imp_t *list)
{
    void *base = list->arr;
    base = &(list->arr[0]);


    qsort(list->arr,list->size,sizeof(list->arr[0]), compare);
}

void destroy_list(str_list_t *l)
{
    if (l)
    {
        str_list_imp_t *list = (str_list_imp_t*)l;
        size_t i;
        for (i=0;i < list->size; i++)
        {
            free(list->arr[i]);
        }
        free(list->arr);
        free(list);
    }
}

static void add(str_list_t *l,char *item)
{
    char *s = strdup(item);
    if (s)
    {
        str_list_imp_t *list = (str_list_imp_t*)l;
        list->size++;
        char **reall = (char**)realloc(list->arr,list->size*sizeof(char*));
        if (reall)
        {
                list->arr=reall;
                list->arr[list->size-1]=s;
        }
    }
}
static char *next(str_list_t *l)
{
    if (l)
    {
        str_list_imp_t *list = (str_list_imp_t*)l;
        if (list->index < list->size)
        {
            char *n = list->arr[list->index];
            list->index++;
            return n;
        }
    }
    return NULL;

}
str_list_t *create_list(void)
{
    struct str_list_imp_s *list = (str_list_imp_t *)calloc(sizeof(str_list_imp_t),1);
    if (list)
    {
        list->parent.add = add;
        list->parent.destroy = destroy_list;
        list->parent.next = next;
        list->parent.sort = sort;

    }
    return (str_list_t*)list;
}

