#include "tree_element.h"

struct TREE_ELEMENT* create_element(enum TREE_ELEMENT_TYPE type)
{
    struct TREE_ELEMENT* elem = malloc(sizeof(struct TREE_ELEMENT));
    elem->type = type;

    // initialise all fields to default values
    elem->child1 = NULL;
    elem->child2 = NULL;
    elem->name_value = NULL;
    elem->name_value_len = 0;
    elem->arithmetic_type = ARITH_ADDITION;
    elem->number_value = 0;

    return elem;
}

struct TREE_ELEMENT* create_name_element(char* value, size_t value_len)
{
    struct TREE_ELEMENT* elem = create_element(TYPE_NAME);
    elem->name_value = value;
    elem->name_value_len = value_len;
    return elem;
}

struct TREE_ELEMENT* create_number_element(double value)
{
    struct TREE_ELEMENT* elem = create_element(TYPE_NUMBER);
    elem->number_value = value;
    return elem;
}

struct TREE_ELEMENT* create_arithmetic_element(enum ARITHMETIC_TYPE type)
{
    struct TREE_ELEMENT* elem = create_element(TYPE_ARITHMETIC);
    elem->arithmetic_type = type;
    return elem;
}