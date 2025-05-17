#include <math.h>
#include <stdio.h>
#include <assert.h>

#include "cases.h"

const static double nan = 0.0 / 0.0;
const static double inf = 1.0 / 0.0;

static double sum(double* iterable, int len)
{
    double res = 0;
    for(int i=0;i<len;i++)
    {
        res += iterable[i];
    }
    return res;
}

int main()
{
    return 0;
}

