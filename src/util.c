#include <stdio.h>
#include <stdlib.h>
#include "util.h"


int int_compar(const void *p1, const void *p2)
{
    return((*(int*)p1) - (*(int*)p2));
}
