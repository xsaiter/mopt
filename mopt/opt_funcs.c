#include <math.h>
#include "opt_spec.h"

double target_func(double *x)
{
    return rosenbrock_func(x);
}

double rosenbrock_func(double *x)
{
    return 100 * (x[1] - x[0] * x[0])*(x[1] - x[0] * x[0]) + (1 - x[0])*(1 - x[0]);
}

double himmelblau_func(double *x)
{
    return pow(x[0] * x[0] + x[1] - 11, 2) + pow(x[0] + x[1] * x[1] - 7, 2);
}

double booth_func(double *x)
{
    return pow(x[0] + 2 * x[1] - 7, 2) + pow(2 * x[0] + x[1] - 5, 2);
}