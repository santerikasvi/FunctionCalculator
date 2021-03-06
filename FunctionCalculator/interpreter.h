#ifndef _H_INTERPRETER
#define _H_INTERPRETER

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

#include "tree_element.h"
#include "hashtable.h"
#include "CALCERR.h"
#include "pointer_help.h"
#include "func.h"
#include "linked_list.h"

#define FOREACH_EXT_FUNC_ONE_ARG(FUNC)                                         \
    FUNC(sin)                                                                  \
    FUNC(cos)                                                                  \
    FUNC(tan)                                                                  \
    FUNC(asin)                                                                 \
    FUNC(acos)                                                                 \
    FUNC(atan)                                                                 \
    FUNC(sinh)                                                                 \
    FUNC(cosh)                                                                 \
    FUNC(tanh)                                                                 \
    FUNC(log)                                                                  \
    FUNC(log10)                                                                \
    FUNC(sqrt)                                                                 \
    FUNC(floor)                                                                \
    FUNC(ceil)

#ifndef CREATE_FUNC
#define CREATE_FUNC_ONE_ARG(FUNC)                                              \
    if (!ht_set(functions_ht, #FUNC, strlen(#FUNC),                            \
                create_ext_func_one_arg(FUNC), NULL, FREE_ENTRY_TRUE)) {       \
        return CALCERR_VALUE_SET_FAILED;                                       \
    }

#endif

#ifndef GENERATE_STRING
#define GENERATE_STRING(STR) #STR,
#endif

int is_name_reserved(char*);

enum CALCERR init_interpreter(void);
enum CALCERR free_interpreter(void);
enum CALCERR load_uservalues(void);
enum CALCERR save_uservalues(void);
void clear_uservalues(void);
/* extra_names is for function args when called */
enum CALCERR evaluate_element(struct TREE_ELEMENT* elem, struct HASHTABLE* extra_names);

enum CALCERR add_ans(double ans);
enum CALCERR get_ans(int index, double* out);
void print_ans(void);
enum CALCERR save_ans(void);
enum CALCERR load_ans(void);
void clear_ans(void);

#endif
