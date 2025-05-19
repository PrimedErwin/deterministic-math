#include <math.h>
#include <stdio.h>
#include <assert.h>
#ifndef __APPLE__
    #include <malloc.h>
#else
    #include <stdlib.h>
#endif
#include "cases.h"

#define TEST_TIME 1000
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
    double* case_sum = (double*)malloc(CASES_COUNT*sizeof(double));
    double* ref_ans_sum = (double*)malloc(TEST_TIME*sizeof(double));
    double* ref_ans_fsum = (double*)malloc(TEST_TIME*sizeof(double));

    for(int i=0;i<TEST_TIME;i++)
    {
        for(int j=0;j<CASES_COUNT;j++)
        {
            int select_index = (int)((cases[j].a + cases[j].b)*i) % 2;
            if(select_index == 0) case_sum[j] = cases[j].a;
            else case_sum[j] = cases[j].b;
        }
        ref_ans_sum[i] = sum(case_sum, CASES_COUNT);
        ref_ans_fsum[i] = fsum_main(case_sum, CASES_COUNT);
    }

    printf("Printing result to case_result.txt ...\n");
    FILE* fp = freopen("case_result.txt", "w", stdout);
    for(int i=0;i<TEST_TIME;i++)
    {
        printf("%e,%llx\n", ref_ans_sum[i], asuint64(ref_ans_sum[i]));
        // volatile float x = (float)ref_ans[i];
        // volatile float y = x;
        // printf("%e,%x\n", y, asuint(y));
    }
    for(int i=0;i<TEST_TIME;i++)
    {
        printf("%e,%llx\n", ref_ans_fsum[i], asuint64(ref_ans_fsum[i]));
    }
    fclose(fp);
    free(case_sum);
    return 0;
}

