#include <math.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

static inline int isclose(double a, double b)
{
    return fabs(a - b) <= DBL_EPSILON;
}

static double sum(double* iterable, int len)
{
    double res = 0;
    for(int i=0;i<len;i++)
    {
        res += iterable[i];
    }
    return res;
}

void test_case_write()
{
    double anssum, ansfsum;
    double* iterable = (double*)malloc(99999*sizeof(double));
    // for(int i=0;i<5000;i++) iterable[i] = sin(i);
    // for(int i=5000;i<9999;i++) iterable[i] = cos(i);
    srand(time(NULL));
    FILE* fp = freopen("basic_op.txt", "w", stdout);
    for(int i=0;i<99999;i++) 
    {
        iterable[i] = (double)rand() / rand();
        while(iterable[i] > 2)
        {
            iterable[i] = (double)rand() / rand();
        }
        if(i % 2) iterable[i] = -iterable[i];
        printf("%.18f\n",iterable[i]);
    }

    anssum = 0.0;
    for(int i=0;i<99999;i++)
    {
        anssum += iterable[i];
        printf("%.18f\n", anssum);
    }
    fclose(fp);
    free(iterable);
    return 0;
}