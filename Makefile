NAME = cub3D
CC = cc 
FLAGS = -Wall -Werror -Wextra

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)
OBJ_DIR = build
INC = include/cub3D.h
MLX42 = libs/MLX42/build/libmlx42.a

all:$(NAME)

$(NAME): $(MLX42) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) \
	$(MLX42) -Iinclude \
	-ldl -lglfw -pthread -lm \
	-o $@

$(MLX42):
	@cd libs/MLX42; cmake -B build; cmake --build build -j4

bonus:
	@echo "bonus"
build/%.o: src/%.c $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)
	mkdir docs external tests data examples extras tools;

clean: 
	@$(RM) $(OBJ)
	@echo "Removing $(OBJ)"
	@cmake --build libs/MLX42/build --target clean
	@echo "Removing MLX42 build objects..."

fclean: clean 
	@$(RM) $(NAME)
	@echo "Removing $(NAME)..."
	@$(RM) -rf libs/MLX42/build
	@echo "Removing MLX42 build directory..."

re: clean all

.PHONY:all clean fclean re
