#include "libm.h"
#include <stdio.h>
#include <assert.h>
#ifndef __APPLE__
    #include <malloc.h>
#else
    #include <stdlib.h>
#endif
#include "cases.h"

#define TEST_TIME 10000
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

static double fsum_main(double* aptr, int n)
{

	/*Kahan sum for float addition*/
	double sum = 0, C = 0, Y, T;
	for (int i = 0; i < n; i++)
	{
		Y = aptr[i] - C;
		T = sum + Y;
		C = T - sum - Y;
		sum = T;
	}
	return sum;
}

int main()
{
    // double* sin_cal = (double*)malloc(TEST_TIME*sizeof(double));

    printf("Printing result to case_result.txt ...\n");
    FILE* fp = freopen("case_result.txt", "w", stdout);
    for(int i=0;i<TEST_TIME;i++)
    {
        double sin_val = sin(cases[i].a);
        printf("%f,%llx\n", sin_val, asuint64(sin_val));
        // volatile float x = (float)ref_ans[i];
        // volatile float y = x;
        // printf("%e,%x\n", y, asuint(y));
    }
    fclose(fp);
    // free(sin_cal);
    return 0;
}

