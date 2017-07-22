#include <math.h>
#include "opt_funcs.h"

double target_func(double *x) {
        return 100 * (x[1] - x[0] * x[0])*(x[1] - x[0] * x[0]) + (1 - x[0])*(1 - x[0]);
}