
cmake_minimum_required(VERSION 3.10)
add_compile_options(-Wall -Wextra -Werror)

project(ft)

include_directories(include PRIVATE include)

add_library(
	${PROJECT_NAME} STATIC
	src/ft_putstring_fd.c
	src/ft_split.c
	src/ft_strlen.c
	src/ft_strncmp.c
	src/ft_strlcpy.c
)

