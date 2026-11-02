cmake_minimum_required(VERSION 3.16)
project(LR1CPP CXX)

# Файлы модулей структур данных и главный файл программы
add_executable(dbms
    array.cpp
    slist.cpp
    dlist.cpp
    stack.cpp
    queue.cpp
    cbtree.cpp
    main.cpp
)

target_include_directories(dbms PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(dbms PROPERTIES CXX_STANDARD 17 CXX_EXTENSIONS OFF)
target_compile_options(dbms PRIVATE -Wall -Wextra)