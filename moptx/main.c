#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void compile_prog()
{
    const char *s = "gcc prog/main.c prog/opt_nelder_mead.c prog/opt_funcs.c -lm -o prog/res";        
    fflush(NULL);    
    int code = system(s);    
    if (code) {
        fprintf(stderr, "compilation %s failed with %d\n", s, code);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char** argv)
{
    compile_prog();
    
    pid_t pid = fork();

    if (pid == 0) { /*child*/
        execv("prog/res", NULL);
        exit(EXIT_SUCCESS);
    } else { /*parent*/
        waitpid(pid, 0, 0);
    }
    
    return (EXIT_SUCCESS);
}