#ifndef OPT_CORE_H
#define OPT_CORE_H

#define NX 2

#ifdef __cplusplus
extern "C" {
#endif  

    typedef struct{        
        double x[NX];
        double y;
    } point;
    
    void point_print(point *p);

#ifdef __cplusplus
}
#endif

#endif /* OPT_CORE_H */