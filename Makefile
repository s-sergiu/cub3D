NAME = cub3D
CC = cc 
FLAGS = -g -Wall -Werror -Wextra

SRC = $(wildcard src/*/*.c) $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/obj/%.o)
DEPS = include
MLX_INC = external/MLX42/include
INC_DIRS = $(wildcard libs/*/include)
INC_FLAGS = $(addprefix -I,$(INC_DIRS))

OBJ_DIR = build/obj

MLX42 = external/MLX42/build/libmlx42.a
LIBARRTOOLS = build/libs/libarrtools/libarrtools.a
LIBARRTOOLS_OBJ = build/libs/libarrtools
LIBFT = build/libs/Libft/libft.a
LIBFT_OBJ_DIR = build/libs/Libft

LIBFT_DIR = libs/Libft
LIBARRTOOLS_DIR = libs/libarrtools
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


all: $(NAME)

submodule_update: 
	@git submodule init
	@git submodule update

$(NAME): $(OBJ_DIR) $(MLX42) $(OBJ) $(LIBFT) $(LIBARRTOOLS) 
	$(CC) $(FLAGS) $(OBJ) -lft -L$(LIBFT_OBJ_DIR) \
	$(MLX42) -Iinclude -larrtools -L$(LIBARRTOOLS_OBJ) \
	$(MLX_FLAGS) -o $@

$(LIBFT): 
	$(MAKE) -C $(LIBFT_DIR)
	mv $(LIBFT_DIR)/libft.a $(LIBFT)
	$(RM) -rf $(LIBFT_DIR)/build

$(LIBARRTOOLS): 
	$(MAKE) -C $(LIBARRTOOLS_DIR)
	mv $(LIBARRTOOLS_DIR)/libarrtools.a $(LIBARRTOOLS)
	$(RM) -rf $(LIBARRTOOLS_DIR)/build

$(MLX42): 
	cd external/MLX42; cmake -B build; cmake --build build -j4


build/obj/%.o: %.c 
	$(CC) $(FLAGS) -I$(DEPS) -I$(MLX_INC) $(INC_FLAGS) -c $< -o $@ 

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) 
	mkdir -p $(OBJ_DIR)/init
	mkdir -p $(OBJ_DIR)/memory
	mkdir -p $(LIBFT_OBJ_DIR)
	mkdir -p $(LIBARRTOOLS_OBJ)

clean: 
	$(RM) $(OBJ) $(MAPOBJ) $(LIBFT) $(LIBARRTOOLS)
	echo "Removing $(OBJ) $(MAPOBJ)"
	cmake --build external/MLX42/build --target clean
	echo "Removing MLX42 build objects..."

fclean: clean 
	$(RM) $(NAME)
	echo "Removing $(NAME)..."
	$(RM) -rf external/MLX42/build
	echo "Removing MLX42 build directory..."

re: clean all

.PHONY:all clean fclean re
