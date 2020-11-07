#ifndef MY_ZSH
#define MY_ZSH


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include "my_readline.h"

#define true 1
#define false 0

typedef struct s_tok
{
        char type;
        char sub_type;
        char *value;
} tok;

typedef struct s_arr_tok
{
        int size;
        tok *arr;
} arr_tok;

//Read and analyze
int prompt(char **);
arr_tok *parser(const char *);
void clear_tokens(arr_tok *);

//Binaries
int executor(char **, char **);

//Builtins
int echo(arr_tok *, char **);
int cd(arr_tok *, char **);

//Env
int my_env(char **);
int my_setenv(const char *, const char *, int, char **);
int my_unsetenv(const char *, char **);
void clear_envp(char **);
char **malloc_env(char **);
char * my_env_var(const char *, char **);

#endif //MY_ZSH