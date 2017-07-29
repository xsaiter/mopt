#ifndef OPT_FUNCS_H
#define OPT_FUNCS_H

#ifdef __cplusplus
extern "C" {
#endif    

    double target_func(double *x);
    double rosenbrock_func(double *x);
    double himmelblau_func(double *x);
    double booth_func(double *x);

#ifdef __cplusplus
}
#endif

#endif /* OPT_FUNCS_H */

