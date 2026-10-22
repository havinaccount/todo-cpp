cmake_minimum_required(VERSION 3.16)

project(todo-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(todo-cpp
		src/main.cpp
		src/logic.cpp
		include/logic.hpp
)

target_include_directories(todo-cpp PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(todo-cpp PRIVATE
		-Wall
		-Wextra
		-Wpedantic
		-Wconversion
		-Wshadow
		-Wformat=2
		-Wcast-qual
		-Wcast-align
)

include(GNUInstallDirs)

install(TARGETS todo-cpp
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)