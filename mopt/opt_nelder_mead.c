#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include<time.h>

#include "opt_spec.h"
#include "opt_funcs.h"

#define NS (NX + 1)
#define EPSILON 0.0001

#define FOR_X for (int i=0;i<NX;++i)
#define FOR_S for (int j=0;j<NS;++j)

inline static double func(point *p)
{
    return target_func(p->x);
}

typedef struct {
    point *points[NS];
} simplex;

static void sx_init(simplex *sx)
{
    FOR_S{
        sx->points[j] = malloc(sizeof (point));
    }
}

static void sx_destroy(simplex *sx)
{
    FOR_S{
        free(sx->points[j]);
    }
}

static void sx_populate(simplex *sx)
{
    int r, sign;
    time_t t;
    srand((unsigned) time(&t));

    FOR_S{
        FOR_X
        {
            r = rand();
            sign = r % 2 == 0 ? 1 : -1;
            sx->points[j]->x[i] = sign * (rand() % 100);
        }
    }
}

static void sx_calculate_func(simplex *sx)
{
    for (int i = 0; i < NS; ++i) {
        sx->points[i]->y = func(sx->points[i]);
    }
}

static int p_sort_cmp(const void *arg1, const void *arg2)
{
    point **a = (point**) arg1;
    point **b = (point**) arg2;
    return ((*a)->y < (*b)->y) ? 1 : -1;
}

static void p_add(const point *a, const point *b, point *r)
{
    FOR_X{
        r->x[i] = a->x[i] + b->x[i];
    }
}

static void p_sub(const point *a, const point *b, point *r)
{
    FOR_X{
        r->x[i] = a->x[i] - b->x[i];
    }
}

static void p_mul(const point *a, double n, point *r)
{
    FOR_X{
        r->x[i] = a->x[i] * n;
    }
}

static void p_div(const point *a, double n, point *r)
{
    FOR_X{
        r->x[i] = a->x[i] / n;
    }
}

static inline void p_copy(point *dest, const point *src)
{
    memcpy(dest, src, sizeof (point));
}

static int sx_stop(const simplex *sx)
{
    double m, d;
    for (int j = 0; j < NX; ++j) {
        m = 0.0;
        d = 0.0;
        for (int i = 0; i < NS; ++i) {
            m += sx->points[i]->x[j];
        }
        m /= NS;
        for (int i = 0; i < NS; ++i) {
            d += pow(sx->points[i]->x[j] - m, 2);
        }
        d /= NS;
        if (d > EPSILON) {
            return 0;
        }
    }
    return 1;
}

void opt_nelder_mead(point *result)
{
    double alpha = 1.0;
    double beta = 0.5;
    double gamma = 2.0;
    
    point *xh, *xg, *xl;
    double yh, yg, yl;
    point xc, xr, xe, xs;
    point p, q, r;
    simplex sx;
    
    sx_init(&sx);
    sx_populate(&sx);

    while (!sx_stop(&sx)) {
        sx_calculate_func(&sx);
        qsort(sx.points, NS, sizeof (point*), p_sort_cmp);

        xh = sx.points[0];
        yh = xh->y;

        xg = sx.points[1];
        yg = xg->y;

        xl = sx.points[NS - 1];
        yl = xl->y;

        p_add(xg, xl, &p);
        p_div(&p, NX, &xc);

        p_mul(&xc, 1.0 + alpha, &p);
        p_mul(xh, alpha, &q);
        p_sub(&p, &q, &xr);
        xr.y = func(&xr);

        if (xr.y < yl) {
            p_mul(&xc, 1.0 - gamma, &p);
            p_mul(&xr, gamma, &q);
            p_add(&p, &q, &xe);
            xe.y = func(&xe);

            if (xe.y < yl) {
                p_copy(xh, &xe);
            } else {
                p_copy(xh, &xr);
            }
        } else {
            if (xr.y <= yg) {
                p_copy(xh, &xr);
            }
        }

        int pass = 0;

        if (yh >= xr.y && xr.y >= yg) {
            p_copy(&p, &xr);
            p_copy(&xr, xh);
            p_copy(xh, &p);
            pass = 1;
        }

        if (xr.y > yh) {
            pass = 1;
        }

        if (pass == 1) {
            p_mul(xh, beta, &p);
            p_mul(&xc, 1.0 - beta, &q);
            p_add(&p, &q, &xs);
            xs.y = func(&xs);
            if (xs.y < yh) {
                p_copy(xh, &xs);
            } else {
                for (int j = 0; j < NS; ++j) {
                    p_sub(sx.points[j], xl, &p);
                    p_div(&p, 2.0, &q);
                    p_add(xl, &q, &r);
                    p_copy(sx.points[j], &r);
                }
            }

        }
    }
    p_copy(result, sx.points[0]);
    sx_destroy(&sx);
}
