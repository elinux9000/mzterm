#ifndef STRING_LIST_H
#define STRING_LIST_H
/*
 * str_list_t is a dynamic list of strings implemented in c with struct inheritance to provide encapsulation.
 */
#ifdef __cplusplus
extern "C"
{
#endif

    struct str_list_s
    {
        void (*destroy)(struct str_list_s *list);
        void (*add)(struct str_list_s *list,const char *item);
        char *(*next)(struct str_list_s *list);
        void (*sort)(struct str_list_s *list);
    };
    typedef struct str_list_s str_list_t;

    //constructor
    str_list_t *create_list(void);

#ifdef __cplusplus
}
#endif

#endif // STRING_LIST_H
