cmake_minimum_required(VERSION 3.10)
project(ctyper VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(ctyper
	src/main.c
	src/terminal.c
	src/fileio.c
	src/ui.c
	src/preloaded_texts.c
)

target_include_directories(ctyper PRIVATE include)
