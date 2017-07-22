#include <stdio.h>
#include <stdlib.h>

#include "opt_spec.h"

int main(int argc, char** argv)
{    
    point result;
    opt_nelder_mead(&result);
    
    printf("point:\nx:");
    for(int i= 0; i< NX; ++i){
        printf("%f ", result.x[i]);
    }
    printf("\ny = %f", result.y);
    return (EXIT_SUCCESS);
}

