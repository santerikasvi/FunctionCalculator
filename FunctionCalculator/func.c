#include "func.h"

struct FUNC* create_func()
{
    struct FUNC* func = malloc(sizeof(struct FUNC));

    if (func == NULL) {
        return NULL;
    }

    func->arg_names = NULL;
    func->arg_count = 0;
    func->func_type = FUNC_TYPE_EXTERNAL;
    func->elem = NULL;
    func->ext_func_one_arg = NULL;
    func->ext_func_two_arg = NULL;

    return func;
}

struct FUNC* create_ext_func_one_arg(/*char* name,*/ double (*ext_func)(double))
{
    struct FUNC* func = create_func();

    if (func == NULL) {
        return NULL;
    }

    // func->name = name;
    func->func_type = FUNC_TYPE_EXTERNAL;
    func->arg_count = 1;
    func->ext_func_one_arg = ext_func;

    return func;
}

struct FUNC* create_ext_func_two_arg(/*char* name,*/
                                     double (*ext_func)(double, double))
{
    struct FUNC* func = create_func();

    if (func == NULL) {
        return NULL;
    }

    // func->name = name;
    func->func_type = FUNC_TYPE_EXTERNAL;
    func->arg_count = 2;
    func->ext_func_two_arg = ext_func;

    return func;
}

struct FUNC* create_intr_func(struct TREE_ELEMENT* elem)
{
    struct FUNC* func = malloc(sizeof(struct FUNC));

    if (func == NULL) {
        return NULL;
    }

    func->func_type = FUNC_TYPE_INTERNAL;
    func->arg_count = elem->args_len;

    func->elem = malloc(sizeof(struct TREE_ELEMENT));

    if (func->elem == NULL) {
        return NULL;
    }

    copy_elem(func->elem, elem->child1);

    func->arg_names = malloc(func->arg_count * sizeof(char*));

    if (func->arg_names == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < func->arg_count; i++) {
        func->arg_names[i] = malloc((elem->args[i]->name_value_len + 1) * sizeof(char));

        if (func->arg_names[i] == NULL) {
            return NULL;
        }

        strncpy_s(func->arg_names[i], (elem->args[i]->name_value_len + 1) * sizeof(char), elem->args[i]->name_value,
                elem->args[i]->name_value_len * sizeof(char));
    }

    return func;
}

enum CALCERR call_func(struct FUNC* func, double** args, size_t args_count,
                       double* out)
{
    enum CALCERR error = CALCERR_NONE;

    if (args_count != func->arg_count) {
        return CALCERR_ARG_COUNT_MISMATCH;
    }

    if (func->func_type == FUNC_TYPE_EXTERNAL) {
        if (func->arg_count == 1) {
            *out = (*func->ext_func_one_arg)(*args[0]);
        } else if (func->arg_count == 2) {
            *out = (*func->ext_func_two_arg)(*args[0], *args[1]);
        } else {
            return CALCERR_ARG_COUNT_MISMATCH;
        }
    } else {
        struct HASHTABLE* args_ht = ht_create(32);

        for (size_t i = 0; i < func->arg_count; i++) {
            if (!ht_set(args_ht, func->arg_names[i], strlen(func->arg_names[i]),
                        (void*)double_to_heap(*args[i]), NULL,
                        FREE_ENTRY_TRUE)) {
                return CALCERR_VALUE_SET_FAILED;
            }
        }

        /* this is an ugly hack (seriously, its ugly):
        clone the func's elem and evaluate that.
        this is done because the interpreter is not "stateless" when it comes to
        elements. meaning the same element cannot be evaluated twice if it has a
        name element anywhere in it. it could be fixed but it requires
        rewriting most of the interpreter logic */
        struct TREE_ELEMENT* elem_clone = malloc(sizeof(struct TREE_ELEMENT));

        if (elem_clone == NULL) {
            return CALCERR_MALLOC_FAILED;
        }

        if (!copy_elem(elem_clone, func->elem)) {
            return CALCERR_MALLOC_FAILED;
        }

        error = evaluate_element(elem_clone, args_ht);
        ht_free(args_ht, NULL);
        *out = *elem_clone->number_value;

        free_elem(elem_clone);

        return error;
    }

    return CALCERR_NONE;
}

void free_func(struct FUNC* func)
{
    if (func->arg_names != NULL) {
        for (size_t i = 0; i < func->arg_count; i++) {
            free(func->arg_names[i]);
        }

        free(func->arg_names);
    }

    if (func->elem != NULL) {
        free_elem(func->elem);
    }

    free(func);
}
