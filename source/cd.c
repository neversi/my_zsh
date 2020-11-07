#include "../lib/my_zsh.h"

static int dir_size = 1024;


int cd(arr_tok *args, char **envp)
{
        char dir_path[dir_size];
        if (args->size == 1)
        {
                char *new_dir = my_env_var("HOME", envp);
                if (chdir(new_dir) == -1)
                {
                        perror("Could not find the path or some error occured\n");
                        return -1;
                }
                my_setenv("PWD", new_dir, 1, envp);
                free(new_dir);
        }

        if (args->size == 2)
        {
                if (args->arr[1].type == 'o' && strlen(args->arr[1].value) == 1)
                {
                        char *pwd_dir = my_env_var("PWD", envp);
                        printf("%s\n", pwd_dir);

                        free(pwd_dir);       
                }
                if (args->arr[1].type == 'v')
                {
                        if (chdir(args->arr[1].value) == -1)
                        {
                                perror("cd: No such file or directory\n");
                                return -1;
                        }
                        getcwd(dir_path, dir_size);
                        printf("%s\n", dir_path);
                        my_setenv("PWD", dir_path, 1, envp);
                }
                if (args->arr[1].type == '$')
                {
                        char *new_dir = my_env_var(args->arr[1].value + 1, envp);

                        if (chdir(new_dir) == -1)
                        {
                                perror("cd : No such file or directory\n");
                                return -1;
                        }
                        my_setenv("PWD", new_dir, 1, envp);

                        free(new_dir);
                }
        }
        else if (args->size > 2)
        {
                perror("cd: Too many arguments\n");
                return -1;
        }

        return 0;
}