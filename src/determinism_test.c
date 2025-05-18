#include <math.h>
#include <stdio.h>
#include <assert.h>
#ifndef __APPLE__
    #include <malloc.h>
#else
    #include <stdlib.h>
#endif
#include "cases.h"

#define TEST_TIME 5
#define issame(a, b) (a==b) || (isnan(a) && isnan(b))

static double sum(double* iterable, int len)
{
    double res = 0;
    for(int i=0;i<len;i++)
    {
        res += iterable[i];
    }
    return res;
}

void double2binary(double input, char* output)
{
    unsigned long long _i = asuint64(input);
    for(int i=0;i<64;i++)
    {
        output[63-i] = (_i & 1)? '1': '0';
        _i = _i >> 1;
    }
}

void calculate_result(double* result)
{
    for(int i=0;i<CASES_COUNT;i++)
    {
        char op = cases[i].op;
        switch (op)
        {
        case '+':
            result[i] = cases[i].a + cases[i].b;
            break;
        case '-':
            result[i] = cases[i].a - cases[i].b;
            break;
        case '*':
            result[i] = cases[i].a * cases[i].b;
            break;
        case '/':
            result[i] = cases[i].a / cases[i].b;
            break;
        default:
            break;
        }
    }
}

int main()
{
    double* ref_ans = (double*)malloc(CASES_COUNT*sizeof(double));
    int test_time = 0;
    calculate_result(ref_ans);
    while(test_time < TEST_TIME)
    {
        test_time++;
        double result;
        for(int i=0;i<CASES_COUNT;i++)
        {
            char op = cases[i].op;
            switch (op)
            {
            case '+':
                result = cases[i].a + cases[i].b;
                break;
            case '-':
                result = cases[i].a - cases[i].b;
                break;
            case '*':
                result = cases[i].a * cases[i].b;
                break;
            case '/':
                result = cases[i].a / cases[i].b;
                break;
            default:
                break;
            }
            assert(issame(result, ref_ans[i]));
        }
    }
    printf("Printing result to case_result.txt ...\n");
    FILE* fp = freopen("case_result.txt", "w", stdout);
    for(int i=0;i<CASES_COUNT;i++)
    {
        printf("%f,%llx\n", ref_ans[i], asuint64(ref_ans[i]));
    }
    fclose(fp);
    free(ref_ans);
    return 0;
}

