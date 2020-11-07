#include "../lib/my_zsh.h"

/**
 * Systematically divides command, options, values in the array of tokens
 * struct tok - type, subtype, value
 * type - command (c), value (v), option (v), environ ($)
 * subtype (only for command) - shell (s), builtin (b)
 * struct arr_tok - size tok*
 */


static void add_tok(tok *, char *, char);
static char handle_command_type(char *value);


arr_tok *parser(const char *original_line)
{
        char *line = (char *)original_line;
        char *value;
        arr_tok *result = (arr_tok *)malloc(sizeof(*result));
        result->arr = (tok *)malloc(sizeof(tok));
        result->size = 0;

        value = strtok(line, " ");
        do
        {
                // printf("%s: %ld \n", value, strlen(value));
                if (strlen(value) < 1) continue;
                result->size += 1;
                result->arr = realloc(result->arr, result->size * sizeof(tok));
                if (result->size == 1)
                {
                        add_tok(&result->arr[0], value, 'c');
                }
                else add_tok(&result->arr[result->size - 1], value, 'n');
        }
        while ((value = strtok(NULL, " ")) != NULL);
        
        return result;
}

void clear_tokens(arr_tok *parser_toks)
{
        free(parser_toks->arr[0].value);
        for (int i = 1; i < parser_toks->size; i++)
        {
                free(parser_toks->arr[i].value);
        }
        free(parser_toks->arr);
        free(parser_toks);
}

static void add_tok(tok *dest, char *value, char type) // dest - destiny, value - string value that should be passed, type - the type of token
{
        dest->value = (char *)malloc(strlen(value) + 1);
        dest->value = strncpy(dest->value, value, strlen(value) + 1);
        dest->type = type;
        if (type == 'c') dest->sub_type = handle_command_type(value);
        if (type == 'n') dest->type = 'v'; 
        if (value[0] == '-') dest->type = 'o';
        if (value[0] == '$') dest->type = '$';
}

static char handle_command_type(char *value) //determing the type of the command (Shell builtin / Binary)
{
        if (strcmp(value, "echo") == 0 ||
                strcmp(value, "cd") == 0 || 
                strcmp(value, "setenv") == 0 || 
                strcmp(value, "unsetenv") == 0 || 
                strcmp(value, "env") == 0 || 
                strcmp(value, "exit") == 0)
                {
                        return 's';
                }
        return 'b';
}