cmake_minimum_required(VERSION 3.10)

project(cub3D)

function(init_git_submodules)
	EXECUTE_PROCESS(COMMAND git submodule init)
	EXECUTE_PROCESS(COMMAND git submodule update)
endfunction()

init_git_submodules() 

if (CMAKE_BUILD_TYPE STREQUAL "TEST")
	set(CMAKE_CXX_STANDARD 14)

	include(FetchContent)
	FetchContent_Declare(
	  googletest
	  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
	)
	# For Windows: Prevent overriding the parent project's compiler/linker settings
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	FetchContent_MakeAvailable(googletest)

	enable_testing()

	add_subdirectory(external/MLX42)
	add_subdirectory(libs/Libft)

	add_executable(
	  hello_test
	  tests/hello_test.cc
	  ../src/error_handling.c
	  ../src/read_map.c
	)
	include_directories(include PRIVATE include/Libft)
	target_link_libraries(
	  hello_test
	  GTest::gtest_main
	  ft
	  mlx42
	)

	include(GoogleTest)
	gtest_discover_tests(hello_test)
else()
	add_compile_options(-Wall -Wextra -Werror)
	add_subdirectory(external/MLX42)
	add_subdirectory(libs/Libft)
	add_subdirectory(libs/libarrtools)
	add_executable(
		${PROJECT_NAME} 
		src/main.c
		src/draw_map_utils.c
		src/draw_map.c
		src/error_handling.c
		src/read_map.c
	)
	include_directories(include PRIVATE libs/Libft/include)
	include_directories(include PRIVATE libs/libarrtools/include)
	target_link_libraries(${PROJECT_NAME} PRIVATE  mlx42 ft arrtools)
endif()
