#include "math.h"

float __math_invalidf(float x)
{
	return (x - x) / (x - x);
}
