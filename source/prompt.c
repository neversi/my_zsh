#include "../lib/my_zsh.h"

static char **toks_to_args(arr_tok *);

int prompt(char **envp)
{
        int leave = true;
        printf("ABDR \%%> ");
        char *line = get_line();
        
        arr_tok *toks = parser(line);
        char **args = toks_to_args(toks);
        
        if (strcmp(toks->arr[0].value, "exit") == 0)
        {
                leave = false;
        }

        if (toks->arr[0].sub_type == 'b')
        {
                executor(args, envp);
        }
        if (toks->arr[0].sub_type == 's')
        {
                // handle_builtins;
        }

        if (strcmp(toks->arr[0].value, "echo") == 0)
        {
                echo(toks, envp);
        }
        else if(strcmp(toks->arr[0].value, "env") == 0)
        {
                my_env(envp);
        }
        else if (toks->size > 3 && strcmp(toks->arr[0].value, "setenv") == 0)
        {
                if (my_setenv(toks->arr[1].value, toks->arr[2].value, atoi(toks->arr[3].value), envp) == -1)
                {
                        printf("ERROR");
                }
        }
        else if (toks->size >= 2 && strcmp(toks->arr[0].value, "unsetenv") == 0)
        {
                my_unsetenv(toks->arr[1].value, envp);
        }

        else if (toks->size >= 1 && strcmp(toks->arr[0].value, "cd") == 0)
        {
                cd(toks, envp);
        }
        
        

        free(args);
        clear_tokens(toks);
        free(line);
        return leave;
}

static char **toks_to_args(arr_tok *toks)
{
        char **args = malloc(sizeof(char *) * (toks->size + 1));
        int i = 0;
        for (; i < toks->size; i += 1)
        {
                args[i] = toks->arr[i].value;
        }
        args[i] = NULL;
        return args;
}