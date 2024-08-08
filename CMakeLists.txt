cmake_minimum_required(VERSION 3.25)
project(cs50 C)

set(CMAKE_C_STANDARD 23)

set(PROJECT_SOURCE_DIR  "/home/elias/projetos/cs50/problems/2024/x/")


# Recover
#set(Sources ${PROJECT_SOURCE_DIR}/recover/recover.c)

# Filter
set(Sources ${PROJECT_SOURCE_DIR}/filter-more/filter.c ${PROJECT_SOURCE_DIR}/filter-more/helpers.c)
set(Headers ${PROJECT_SOURCE_DIR}/filter-more/helpers.h ${PROJECT_SOURCE_DIR}/filter-more/bmp.h)

add_executable(cs50 ${Sources} ${Headers})
target_link_libraries(cs50 m)
