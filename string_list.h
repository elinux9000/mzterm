#ifndef STRING_LIST_H
#define STRING_LIST_H
struct str_list_s
{
    void (*destroy)(struct str_list_s *list);
    void (*add)(struct str_list_s *list,char *item);
};
typedef struct str_list_s str_list_t;
str_list_t *create_list(void);
#endif // STRING_LIST_H
