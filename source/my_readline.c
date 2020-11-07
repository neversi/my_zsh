/**
 * @brief read the line from stream, line is considered untill \n or eof is reached
 * !!! It is Revised and Resubmitted work, now it works fine and without any buggy stuffs
 * !!! Reason of previous errors was uncompleted understanding of the task. 
 * !!! And also string functions that were used in this task were recreated before by me so 
 * !!! the using of these ones could be used () but in functions.c file the implementation of that functions were provided
 * @param fd is integer which describes file descriptor
 * @see my_readline(int fd)
 * @
 */
#include "../lib/my_readline.h"

char *my_readline(int fd)
{
    static char str[READLINE_READ_SIZE] = "";
    char *line = NULL;
    size_t count = READLINE_READ_SIZE;
    char buf[count + 1];
    size_t index = 0;

    while (index < strlen(str))
    {
        if (str[index] == '\n') break;
        index++;
    }
    if (index < strlen(str))
    {
        if (index == 0)
        {
            line = (char *)malloc(1);
            line = strcpy(line, "");
        } else
        {
            line = (char *)malloc((index + 1)* sizeof(char));
            line = strncpy(line, str, index);
            // line[index] = 0;
        }
        size_t start_i = ++index;
        size_t size_str = strlen(str);
        for (;index < size_str; index++)
        {
            str[index - start_i] = str[index];
        }
        while (index - start_i < count)
        {
            str[index - start_i] = 0;
            index++;
        }
        return line;
    }

    index = 0;
    int flag = 1;
    while (flag)
    {
        ssize_t num_bytes = read(fd, buf, count);
        if (num_bytes == -1)
        {
            printf("The error occured");
            return NULL;
        }
        if (num_bytes == 0 && strlen(str) == 0) return line;
        buf[num_bytes] = 0;

        while (index < strlen(buf))
        {
            if (buf[index] == '\n') break;
            index++;
        }
        if (index < strlen(buf))
        {
            if (!line)
            {
                line = (char *)malloc((strlen(str) + index + 1) * sizeof(char));
                line = strcpy(line, str);
                line = strncat(line, buf, index);  
                line[strlen(str) + index] = 0;
            } else
            {
                line = (char *)realloc(line, strlen(line) + index + 1);
                size_t length = strlen(line);
                line = strncat(line, buf, index);
                line[length + index] = 0;

            }
            size_t size_str = strlen(str);
            for (size_t i = 0; i < size_str; i++) str[i] = 0;
            size_t start_i = ++index;
            for (; index < strlen(buf); index++)
            {
                str[index - start_i] = buf[index];
            }
            str[index - 1] = 0;
            flag = 0;
        } else 
        {
            if(!line)
            {
                line = (char *)malloc(strlen(str) + strlen(buf) + 1);
                line = strcpy(line, str);
                line = strcat(line, buf);
                for (size_t i = 0; i < count; i++) str[i] = 0;
            } else
            {
                line = (char *)realloc(line, strlen(line) + strlen(buf) + 1);
                size_t length = strlen(line) + strlen(buf);
                line = strcat(line, buf);
                line[length] = 0;                
            }
            size_t size_str = strlen(str);
            for (size_t i = 0; i < size_str; i++) str[i] = 0;
        }
        index = 0;
    }
    return line;
}


/*
    loop (str[index] != n/eof) index_s = \n
    
    str < index -> line
    str > index -> str
    return line 

    read -> buf
    loop (buf[index] != n/eof) index_b = \n
    
    str + buf < index -> line 
    buf > index -> str
    return line
*/