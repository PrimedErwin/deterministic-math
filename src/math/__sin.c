/* origin: FreeBSD /usr/src/lib/msun/src/k_sin.c */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
/* __sin( x, y, iy)
 * kernel sin function on ~[-pi/4, pi/4] (except on -0), pi/4 ~ 0.7854
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 * Input iy indicates whether y is 0. (if iy=0, y assume to be 0).
 *
 * Algorithm
 *      1. Since sin(-x) = -sin(x), we need only to consider positive x.
 *      2. Callers must return sin(-0) = -0 without calling here since our
 *         odd polynomial is not evaluated in a way that preserves -0.
 *         Callers may do the optimization sin(x) ~ x for tiny x.
 *      3. sin(x) is approximated by a polynomial of degree 13 on
 *         [0,pi/4]
 *                               3            13
 *              sin(x) ~ x + S1*x + ... + S6*x
 *         where
 *
 *      |sin(x)         2     4     6     8     10     12  |     -58
 *      |----- - (1+S1*x +S2*x +S3*x +S4*x +S5*x  +S6*x   )| <= 2
 *      |  x                                               |
 *
 *      4. sin(x+y) = sin(x) + sin'(x')*y
 *                  ~ sin(x) + (1-x*x/2)*y
 *         For better accuracy, let
 *                   3      2      2      2      2
 *              r = x *(S2+x *(S3+x *(S4+x *(S5+x *S6))))
 *         then                   3    2
 *              sin(x) = x + (S1*x + (x *(r-y/2)+y))
 */

#include "math.h"

static const double
S1  = -1.66666666666666324348e-01, /* 0xBFC55555, 0x55555549 */
S2  =  8.33333333332248946124e-03, /* 0x3F811111, 0x1110F8A6 */
S3  = -1.98412698298579493134e-04, /* 0xBF2A01A0, 0x19C161D5 */
S4  =  2.75573137070700676789e-06, /* 0x3EC71DE3, 0x57B1FE7D */
S5  = -2.50507602534068634195e-08, /* 0xBE5AE5E6, 0x8A2B9CEB */
S6  =  1.58969099521155010221e-10; /* 0x3DE5D93A, 0x5ACFD57C */

double __sin(double x, double y, int iy)
{
	double z,r,v,w;
	printf("6bp%f,%llx\n",x,asuint64(x));
	printf("7bp%f,%llx\n",y,asuint64(y));
	z = x*x;
	w = z*z;
	r = S2 + z*(S3 + z*S4) + z*w*(S5 + z*S6);
	v = z*x;
	printf("8bp%f,%llx\n",z,asuint64(z));
	printf("9bp%f,%llx\n",w,asuint64(w));
	printf("10bp%f,%llx\n",r,asuint64(r));
	printf("11bp%f,%llx\n",v,asuint64(v));
	printf("12bp%f,%llx\n",0.5*y,asuint64(0.5*y));
	printf("13bp%f,%llx\n",v*r,asuint64(v*r));
	printf("14bp%f,%llx\n",(0.5*y - v*r),asuint64((0.5*y - v*r)));
	printf("15bp%f,%llx\n",z*(0.5*y - v*r),asuint64(z*(0.5*y - v*r)));
	printf("16bp%f,%llx\n",(z*(0.5*y - v*r) - y),asuint64((z*(0.5*y - v*r) - y)));
	printf("17bp%f,%llx\n",v*S1,asuint64(v*S1));
	printf("18bp%f,%llx\n",((z*(0.5*y - v*r) - y) - v*S1),asuint64(((z*(0.5*y - v*r) - y) - v*S1)));
	printf("4bp%f,%llx\n",x - ((z*(0.5*y - v*r) - y) - v*S1),asuint64(x - ((z*(0.5*y - v*r) - y) - v*S1)));
	if (iy == 0)
		return x + v*(S1 + z*r);
	else
		return x - ((z*(0.5*y - v*r) - y) - v*S1);
}
