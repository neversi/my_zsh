#include "../lib/my_zsh.h"

char *get_line()
{
        char *command = (char *)malloc(sizeof(char));
        int len = 0;
        char ch;
        while ((ch = getchar()) != '\n')
        {
                len++;
                command = (char *)realloc(command, (len + 1) * sizeof(char));
                command[len - 1] = ch;
        }
        command[len] = 0;
        return command;
}