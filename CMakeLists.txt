cmake_minimum_required(VERSION 3.26.3)
add_compile_options(-Wall -Wextra -Werror)

project(cub3D)

add_subdirectory(external/MLX42)
add_subdirectory(libs/libft)
add_executable(
	${PROJECT_NAME} 
	src/main.c
	src/draw_map_utils.c
	src/draw_map.c
	src/error_handling.c
	src/read_map.c
)

target_link_libraries(${PROJECT_NAME} mlx42 ft)
