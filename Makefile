NAME = cub3D
CC = cc 
FLAGS = -g -Wall -Werror -Wextra

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)

OBJ_DIR = build

MLX42 = external/MLX42/build/libmlx42.a
LIBFT = build/libft/libft.a
LIBFT_OBJ_DIR = build/libft

MLX_DIR = external/MLX42/include
LIBFT_DIR = libs/libft
VPATH = src

UNAME = $(shell uname -s)
ifeq ($(UNAME),Linux)
MLX_FLAGS = -ldl -lglfw -pthread -lm
endif

ifeq ($(UNAME),Darwin)
BREW = $(shell brew --cellar glfw)
FLAGS += "-mmacosx-version-min=12.06" "-arch" "x86_64"
MLX_FLAGS = -lglfw -L"$(BREW)/3.3.8/lib"
endif

all:$(NAME)

$(NAME): $(OBJ_DIR) $(MLX42) $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) -lft -L $(LIBFT_OBJ_DIR) \
	$(MLX42) -Iinclude \
	$(MLX_FLAGS) -o $@

$(LIBFT): 
	@$(MAKE) -C $(LIBFT_DIR)
	@mv $(LIBFT_DIR)/libft.a $(LIBFT)
	@$(RM) -rf $(LIBFT_DIR)/build

$(MLX42): $(MLX_DIR)
	@cd external/MLX42; cmake -B build; cmake --build build -j4

$(MLX_DIR):
	@git submodule init
	@git submodule update

build/%.o: %.c 

	@$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR) 
	@mkdir -p $(OBJ_DIR)/libft

clean: 
	@$(RM) $(OBJ) $(MAPOBJ) $(LIBFT)
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
