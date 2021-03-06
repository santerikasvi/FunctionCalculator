#ifndef _H_CALCERR
#define _H_CALCERR

#define FOREACH_CALCERR(CALCERR)                                               \
    CALCERR(CALCERR_NONE)                                                      \
    CALCERR(CALCERR_MALLOC_FAILED)                                             \
    CALCERR(CALCERR_REALLOC_FAILED)                                            \
    CALCERR(CALCERR_INTR_INIT_FAILED)                                          \
    CALCERR(CALCERR_VALUE_SET_FAILED)                                          \
    CALCERR(CALCERR_INTR_ELEMENT_NOT_IMPLEMENTED)                              \
    CALCERR(CALCERR_UNEXPECTED_TOKEN)                                          \
    CALCERR(CALCERR_EXPECTED_CLOSING_BRACKET)                                  \
    CALCERR(CALCERR_UNEXPECTED_END_OF_INPUT)                                   \
    CALCERR(CALCERR_DIVIDE_BY_ZERO)                                            \
    CALCERR(CALCERR_INVALID_CHARACTER)                                         \
    CALCERR(CALCERR_INVALID_ELEMENT)                                           \
    CALCERR(CALCERR_NAME_NOT_FOUND)                                            \
    CALCERR(CALCERR_ARG_COUNT_MISMATCH)                                        \
    CALCERR(CALCERR_ARG_TYPE_MISMATCH)                                         \
    CALCERR(CALCERR_ARG_CONVERSION_FAILED)                                     \
    CALCERR(CALCERR_INVALID_ANS_INDEX)                                         \
    CALCERR(CALCERR_NAME_RESERVED)                                             \
    CALCERR(CALCERR_USERVALUE_SAVING_FAILED)                                   \
    CALCERR(CALCERR_USERVALUE_LOADING_FAILED)                                  \
    CALCERR(CALCERR_ANS_SAVING_FAILED)                                         \
    CALCERR(CALCERR_ANS_LOADING_FAILED)

#ifndef GENERATE_ENUM
#define GENERATE_ENUM(ENUM) ENUM,
#endif
#ifndef GENERATE_STRING
#define GENERATE_STRING(STR) #STR,
#endif

enum CALCERR { FOREACH_CALCERR(GENERATE_ENUM) };

#pragma GCC diagnostic ignored "-Wunused-variable"
static const char* CALCERR_STRING[] = {FOREACH_CALCERR(GENERATE_STRING)};

#endif
