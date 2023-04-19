
cmake_minimum_required(VERSION 3.10)
add_compile_options(-Wall -Wextra -Werror)

project(arrtools)

add_library(
	${PROJECT_NAME} STATIC
	src/arrtools_free.c
	src/arrtools_get_height.c
)

