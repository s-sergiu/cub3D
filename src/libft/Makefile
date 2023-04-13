NAME = libft.a
CC = cc 
FLAGS = "-mmacosx-version-min=12.06" -Wall -Werror -Wextra "-arch" "x86_64"

AR = ar rcs

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)

OBJ_DIR = build
INC = ../../include/libft/libft.h

all: $(OBJ_DIR) $(NAME) 

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
