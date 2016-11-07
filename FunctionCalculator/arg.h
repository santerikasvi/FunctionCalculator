#pragma once

#include <stdlib.h>

#include "CALCERR.h"

enum ARG_TYPE {
    ARG_NUMBER, ARG_NAME
};

struct ARG {
    enum ARG_TYPE type;
    void** value;
};

int argcmp(const enum ARG_TYPE*, const size_t, const enum ARG_TYPE*, const size_t);
enum CALCERR create_args(const enum ARG_TYPE*, void***, const size_t, struct ARG***);