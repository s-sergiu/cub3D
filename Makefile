NAME = cub3D
CC = cc 
FLAGS = -Wall -Werror -Wextra

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)
OBJ_DIR = build
INC = include/cub3D.h

all:$(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(INC)
	$(CC) $(FLAGS) $(OBJ) -o $@

build/%.o: src/%.c
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean: 
	$(RM) $(OBJ)

fclean: clean 
	$(RM) $(NAME)

re: clean all

.PHONY:all clean fclean re
