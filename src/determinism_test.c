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
    double* sin_cal = (double*)malloc(TEST_TIME*sizeof(double));

    printf("Printing result to case_result.txt ...\n");
    FILE* fp = freopen("case_result.txt", "w", stdout);
    for(int i=0;i<5000;i++)
    {
        sin_cal[i] = sin(i);
    }
    for(int i=5000;i<9999;i++)
    {
        sin_cal[i] = cos(i);
    }
    double ans_sum = sum(sin_cal, 9999);
    double ans_fsum = fsum(sin_cal, 9999);
    printf("%f,%llx\n", ans_sum, asuint64(ans_sum));
    printf("%f,%llx\n", ans_fsum, asuint64(ans_fsum));
    fclose(fp);
    free(sin_cal);
    return 0;
}

