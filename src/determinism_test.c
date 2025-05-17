#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>

#include "cases.h"

#define TEST_TIME 5
#define issame(a, b) (a==b) || (isnan(a) && isnan(b))

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
    return 0;
}

