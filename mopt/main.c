#include <stdio.h>
#include <stdlib.h>

#include "opt_spec.h"

int main(int argc, char** argv)
{    
    point res;
    opt_nelder_mead(&res);
    
    printf("point:\nx:");
    
    for(int i= 0; i< NX; ++i){
        printf("%f ", res.x[i]);
    }
    
    printf("\ny = %f", res.y);
    
    return (EXIT_SUCCESS);
}