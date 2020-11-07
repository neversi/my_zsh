#include "../lib/my_zsh.h"


int my_env(char **envp)
{
        for (int i = 0; envp[i] != NULL; i += 1)
        {
                if (strlen(envp[i]) > 0) printf("%s\n", envp[i]);
        }
        return 1;
}

char **malloc_env(char **envp)
{
        int size = 0; 
        for (; envp[size] != NULL; size += 1) {}

        char **envp_c = (char **)malloc(sizeof(char *) * (size + 1));
        for (int i = 0; envp[i] != NULL; i += 1)
        {
                envp_c[i] = malloc(sizeof(char) * (strlen(envp[i]) + 1));
                strcpy(envp_c[i], envp[i]);
        }
        envp_c[size] = NULL;

        return envp_c;
}

void clear_envp(char **envp_c)
{
        for (int i = 0; envp_c[i] != NULL; i += 1)
        {
                free(envp_c[i]);
        }

        free(envp_c);
}

int my_setenv(const char *name, const char *value, int overwrite, char **envp)
{
        int does_exist = false;
        int envp_size = 0;
        for (int i = 0; envp[i] != NULL; i += 1)
        {
                int name_size = 0;
                for (; envp[i][name_size] != '='; name_size += 1) {}
                if (strncmp(envp[i], name, name_size) == 0)
                {
                        does_exist = true;

                        if (!overwrite)
                        {
                                break;
                        }

                        if ((envp[i] = realloc(envp[i], sizeof(char) *(strlen(name) + strlen(value) + 2))) == NULL)
                        {
                                perror("Error with setting the environ value");
                                return -1;
                        }

                        strcpy(envp[i], name);
                        strcat(envp[i], "=");
                        strcat(envp[i], value);
                        break;
                }
                envp_size += 1;
        }

        if (does_exist == false)
        {
                if (realloc(envp, sizeof(char *) * (envp_size + 2)) == NULL)
                {
                        perror("Problem with adding new environ value\n");
                        return -1;
                }

                envp[envp_size] = malloc(strlen(name) + strlen(value) + 2);
                strcpy(envp[envp_size], name);
                strcat(envp[envp_size], "=");
                strcat(envp[envp_size], value);
                envp[envp_size + 1] = NULL;
        }

        return 0;
}

int my_unsetenv(const char *name, char **envp)
{
        for (int i = 0; envp[i] != NULL; i += 1)
        {
                int name_size = 0;
                for (; envp[i][name_size] != '='; name_size += 1) {}
                if (strncmp(envp[i], name, name_size) == 0)
                {
                        int j = i;
                        for (; envp[j + 1] != NULL; j += 1)
                        {
                                if ((envp[j] = realloc(envp[j], strlen(envp[j + 1]) + 1)) == NULL)
                                {
                                        perror("Error with unsetting the environ variable\n");
                                        return -1;
                                }
                                strcpy(envp[j], envp[j + 1]);
                        }
                        free(envp[j]);
                        envp[j] = NULL;
                        break;
                }
        }
        return 0;
}

char *my_env_var(const char *var_name, char **envp)
{
        char *my_result = NULL;
        for (int i = 0; envp[i] != NULL; i += 1)
        {
                int key_size = 0;
                for (;envp[i][key_size] != '='; key_size += 1) {}

                {
                        my_result = malloc(strlen(envp[i] + key_size + 1) + 1);
                        strcpy(my_result, envp[i] + key_size + 1);
                }
        }
        return my_result;
}