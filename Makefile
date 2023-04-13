NAME = cub3D
CC = cc 
FLAGS = -g -Wall -Werror -Wextra

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)

MAPSRC = $(wildcard src/map_utils/*.c)
MAPOBJ = $(MAPSRC:src/map_utils/%.c=build/map_utils/%.o)

OBJ_DIR = build
INC = include/cub3D.h

MLX42 = external/MLX42/build/libmlx42.a
LIBFT = build/libft/libft.a

MLX_DIR = external/MLX42/include
LIBFT_DIR = src/libft

UNAME = $(shell uname -s)
ifeq ($(UNAME),Linux)
MLX_FLAGS = -ldl -lglfw -pthread -lm
endif

ifeq ($(UNAME),Darwin)
FLAGS += "-mmacosx-version-min=12.06" "-arch" "x86_64"
MLX_FLAGS = -lglfw -L"/usr/local/Cellar/glfw/3.3.8/lib"
endif

all:$(NAME)

$(NAME): $(OBJ_DIR) $(MLX42) $(OBJ) $(MAPOBJ) $(INC) $(LIBFT)
	$(CC) $(MAPOBJ) $(FLAGS) $(OBJ) build/libft.a \
	$(MLX42) -Iinclude \
	$(MLX_FLAGS) -o $@

$(LIBFT): 
	@make -C $(LIBFT_DIR)
	@mv src/libft/libft.a $(OBJ_DIR)
	@rm -rf src/libft/build

$(MLX42): $(MLX_DIR)
	@cd external/MLX42; cmake -B build; cmake --build build -j4

$(MLX_DIR):
	@git submodule init
	@git submodule update

bonus:
	@echo "bonus"

build/%.o: src/%.c 

	@$(CC) $(FLAGS) -c $< -o $@

build/map_utils/%.o: src/map_utils/%.c 

	@$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR) 
	@mkdir -p build/map_utils
	@mkdir tests examples tools;

clean: 
	@$(RM) $(OBJ) $(MAPOBJ) build/libft.a
	@echo "Removing $(OBJ) $(MAPOBJ)"
	@cmake --build external/MLX42/build --target clean
	@echo "Removing MLX42 build objects..."

fclean: clean 
	@$(RM) $(NAME)
	@echo "Removing $(NAME)..."
	@$(RM) -rf external/MLX42/build
	@echo "Removing MLX42 build directory..."

re: clean all

.PHONY:all clean fclean re
