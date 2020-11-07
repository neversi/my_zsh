#include "../lib/my_zsh.h"

int echo(arr_tok *args, char **envp)
{
        char *result = malloc(1);
        result[0] = 0;
        int consider_backslash = 0;
        int is_after_value = 0;
        int is_newline = 1;
        for (int i = 1; i < args->size; i += 1)
        {
                tok *current = &args->arr[i];
                if (current->type == '$')
                {
                        for (int j = 0; envp[j] != NULL; j += 1)
                        {
                                int key_size = 0;
                                for (;envp[j][key_size] != '='; key_size += 1) {}
                                if (strncmp(current->value + 1, envp[j], key_size) == 0)
                                {
                                        result = realloc(result, strlen(result) + strlen(envp[j]) + 2);
                                        result = strcat(result, envp[j] + strlen(current->value));
                                        result = strcat(result, " ");
                                }
                        }
                        is_after_value = 1;
                }
                else if (current->type == 'o')
                {
                        if (is_after_value)
                        {
                                result = realloc(result, strlen(result) + strlen(current->value) + 2);
                                result = strcat(result, current->value);
                                result = strcat(result, " ");
                                continue;
                        }
                        if (strcmp(current->value, "-n") == 0)
                        {
                                is_newline = 0;
                        }
                        else if (strcmp(current->value, "-E") == 0)
                        {
                                consider_backslash = 0;
                        }
                        else if (strcmp(current->value, "-e") == 0)
                        {
                                consider_backslash = 1;
                        }
                }
                else
                {
                        result = realloc(result, strlen(result) + strlen(current->value) + 2);
                        result = strcat(result, current->value);
                        result = strcat(result, " ");
                        is_after_value = 1;
                }
        }

        if (!consider_backslash)
        {
                int index = 0;
                int is_in_sequence = 0;
                char *copy_result = malloc(strlen(result) + 1);
                for (size_t i = 0; i < strlen(result); i += 1)
                {
                        if (result[i] == '\\')
                        {
                                if (is_in_sequence)
                                {
                                        copy_result[index] = result[i];
                                        index += 1;
                                }
                                is_in_sequence = 1;
                                continue;
                        }
                        copy_result[index] = result[i];
                        is_in_sequence = 0;
                        index += 1;
                }
                copy_result[index] = 0;
                printf("%s", copy_result);
                free(copy_result);
        }
        else printf("%s", result);
        free(result);
        if (is_newline) printf("\n");
        return 1;
}