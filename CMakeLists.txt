cmake_minimum_required(VERSION 3.19)
project(Shell C)

set(CMAKE_C_STANDARD 99)

add_executable(Shell main.c dynamic_list.c dynamic_list.h memory_list.c memory_list.h commands.c commands.h storage_mod.c storage_mod.h memory_func.c memory_func.h memory_aux_func.c memory_aux_func.h)