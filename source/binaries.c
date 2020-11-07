#include "../lib/my_zsh.h"

static char *find_command(char *, char **envp);

int executor(char **args, char **envp)
{
        pid_t pid, wid;
        int status;
        pid = fork();

        if (pid == 0)
        {
                if (args[0][0] == '/' || args[0][0] == '.')
                {
                        if (execve(args[0], args, envp) == -1)
                        {
                                perror("Error with operation\n");
                        }
                }
                else 
                {
                        char *command = find_command(args[0], envp);
                        free(args[0]);
                        args[0] = command;
                        if (command != NULL && execve(args[0], args, envp) == -1)
                        {
                                perror("Error with operation\n");
                        }
                }
                exit(EXIT_FAILURE);
        }
        else
        {
                do 
                {
                        wid = waitpid(pid, &status, WUNTRACED);
                        if (wid) {}
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
        return 1;
}

static char *find_command(char *command_name, char **envp)
{
        char *path_raw = my_env_var("PATH", envp);
        char **path_vars = (char **)malloc(sizeof(char *));
        char *temp = NULL;
        char *resulting_path = NULL;
        int size = 0;
        
        temp = strtok(path_raw, ":");
        do
        {
                size += 1;
                path_vars = (char **)realloc(path_vars, sizeof(char *) * (size + 1));
                path_vars[size - 1] = (char *)malloc(strlen(temp) + 1);
                strcpy(path_vars[size - 1], temp);
                path_vars[size] = NULL;
                temp = strtok(NULL, ":");

        } while (temp != NULL);
        
        for (int i = 0; path_vars[i] != NULL; i += 1)
        {
                temp = (char *)malloc(strlen(path_vars[i]) + strlen(command_name) + 2);
                temp[0] = 0;
                strcat(temp, path_vars[i]);
                strcat(temp, "/");
                strcat(temp, command_name);
                struct stat file_stat;
                if (stat(temp, &file_stat) != 0)
                {}
                else
                {
                        if (file_stat.st_mode & S_IXUSR)
                        {
                                resulting_path = temp;
                                break;
                        }
                }
                free(temp);
        }

        
        free(path_raw);
        for (int i = 0; path_vars[i] != NULL; i += 1)
        {
                free(path_vars[i]);
        }
        free(path_vars);
        if (resulting_path == NULL)
        {
                perror("execve: Command was not found\n");
        }
        return resulting_path;
}