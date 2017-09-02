#ifndef OPT_SPEC_H
#define OPT_SPEC_H

#define NX 2

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef struct {
        double x[NX];
        double y;
    } point;
    
    double target_func(double *x);
    double rosenbrock_func(double *x);
    double himmelblau_func(double *x);
    double booth_func(double *x);

    void opt_nelder_mead(point *result);

#ifdef __cplusplus
}
#endif

#endif /* OPT_SPEC_H */