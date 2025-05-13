#include <math.h>
#include <stdio.h>
#include <assert.h>

static inline int isclose(double a, double b)
{
    return fabs(a - b) <= DBL_EPSILON;
}

int main(int argc, const char* argv[])
{
    assert(isclose(acos(cos(M_PI)), M_PI));
    assert(isclose(acos(cos(M_PI_2)), M_PI_2));
    assert(isclose(acos(cos(M_PI_4)), M_PI_4));
    assert(isclose(acos(cos(M_1_PI)), M_1_PI));
    assert(isclose(acos(cos(M_2_PI)), M_2_PI));

    assert(isclose(asin(sin(M_PI)), 0));
    assert(isclose(asin(sin(M_PI_2)), M_PI_2));
    assert(isclose(asin(sin(M_PI_4)), M_PI_4));
    assert(isclose(asin(sin(M_1_PI)), M_1_PI));
    assert(isclose(asin(sin(M_2_PI)), M_2_PI));

    assert(isclose(atan(tan(M_PI)), 0));
    assert(isclose(atan(tan(M_PI_2)), M_PI_2));
    assert(isclose(atan(tan(M_PI_4)), M_PI_4));
    assert(isclose(atan(tan(M_1_PI)), M_1_PI));
    assert(isclose(atan(tan(M_2_PI)), M_2_PI));

    assert(isclose(atan2(M_PI_4, M_PI_4), M_PI_4));
    assert(isclose(atan2(-M_PI_4, M_PI_4), -M_PI_4));
    assert(isclose(atan2(-M_PI_4, -M_PI_4), -M_PI_4 - M_PI_2));
    assert(isclose(atan2(M_PI_4, -M_PI_4), M_PI_4 + M_PI_2));

    assert(isclose(ceil(M_PI), 4.0f));
    assert(isclose(ceil(-M_PI), -3.0f));
    printf("ceil(NAN) = %.18f\nceil(INF) = %.18f\n", ceil(NAN), ceil(INFINITY));

    assert(isclose(degrees(1), M_RAD2DEG));
    assert(isclose(degrees(-M_PI), -180.0f));

    assert(isclose(exp(0), 1.0f));
    assert(isclose(exp(1), M_E));

    assert(isclose(floor(M_PI), 3.0f));
    assert(isclose(floor(-M_PI), -4.0f));
    printf("floor(NAN) = %.18f\nfloor(INF) = %.18f\n", floor(NAN), floor(INFINITY));

    assert(isclose(fmod(M_PI, M_PI_2), 0.0f));

    assert(isclose(log(2), M_LN2));
    assert(isclose(log(10), M_LN10));
    assert(isclose(log10(M_E), M_LOG10E));
    assert(isclose(log2(M_E), M_LOG2E));

    double intpart, fracpart;
    fracpart = modf(M_PI, &intpart);
    assert(isclose(fracpart, M_PI-3.0f));
    assert(isclose(intpart, 3.0f));

    assert(isclose(pow(M_2_SQRTPI, 2), 4.0f/M_PI));
    assert(isclose(pow(M_SQRT2, 2) / 2, 1.0f));
    assert(isclose(pow(M_SQRT1_2, 2), 0.5f));

    assert(isclose(radians(M_RAD2DEG), 1.0f));
    assert(isclose(radians(-180.0f), -M_PI));

    assert(isclose(scalbn(M_PI_4, 2), M_PI));

    assert(isclose(sqrt(2), M_SQRT2));
    assert(isclose(2/sqrt(M_PI), M_2_SQRTPI));
    assert(isclose(1/sqrt(2), M_SQRT1_2));

    assert(isclose(trunc(M_PI), 3.0f));
    printf("%.18f", sqrt(2)-M_SQRT2);
    return 0;
}
