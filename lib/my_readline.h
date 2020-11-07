#ifndef MY_READLINE 
#define MY_READLINE

#include <stdio.h>
#include <string.h>
// #include "functions.c"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define READLINE_READ_SIZE 2

char *my_readline(int);
char *get_line(void);


#endif //MY_READLINE

