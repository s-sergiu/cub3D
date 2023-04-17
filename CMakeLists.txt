
cmake_minimum_required(VERSION 3.26.3)
add_compile_options(-Wall -Wextra -Werror)

project(cub3D)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

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

enable_testing()

add_executable(
  hello_test
  hello_test.cc
  src/error_handling.c
  src/read_map.c
)
target_link_libraries(
  hello_test
  GTest::gtest_main
  mlx42
  ft
)

include(GoogleTest)
gtest_discover_tests(hello_test)

