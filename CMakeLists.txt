cmake_minimum_required(VERSION 3.16)

project(nigger-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_COMPILER clang-22)
set(CMAKE_CXX_COMPILER clang++-22)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(nigger-cpp
		src/main.cpp
		src/logic.cpp
)

target_include_directories(nigger-cpp PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(nigger-cpp PRIVATE
		-Wall
		-Wextra
		-Wpedantic
		-Wconversion
		-Wshadow
		-Wformat=2
)

include(GNUInstallDirs)

install(TARGETS nigger-cpp
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)