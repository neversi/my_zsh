CC = gcc
FLAGS := -Wall -Werror -Wextra -g -fsanitize=address

FILES := my_readline main parser get_line binaries prompt echo env cd

HEADERS = $(addprefix lib/,my_zsh.h my_readline.h)

OFILES :=$(FILES:=.o)

SFILES :=$(FILES:=.c)

OBJ = $(addprefix obj/,$(OFILES))

SOURCE = $(addprefix source/,$(SFILES))

all: my_zsh

my_zsh: $(OBJ) $(HEADERS)
	$(CC) -I./lib/ -I./source/ -o my_zsh $(OBJ) $(FLAGS)

obj/%.o: source/%.c
	$(CC) -I./lib/ -I./source/ -c $< $(FLAGS) && mv *.o obj/

clean:
	rm -rf obj/*.o my_zsh

re: clean all