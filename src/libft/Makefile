NAME = libft.a
CC = cc 
FLAGS = -g -Wall -Werror -Wextra
AR = ar rcs

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)

OBJ_DIR = build
INC = ../../include/libft.h

all:$(NAME)

$(NAME): $(OBJ) $(INC)
	@$(AR) $(NAME) $^

build/%.o: src/%.c
	@$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean: 
	@$(RM) $(OBJ)
	@echo "Removing $(OBJ)"

fclean: clean 
	@$(RM) $(NAME)
	@echo "Removing $(NAME)..."

re: clean all

.PHONY:all clean fclean re
