project(tree_demo)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_COMPILER             "clang")
set(CMAKE_CXX_COMPILER           "clang++")

message("source dir: ${PROJECT_SOURCE_DIR}")
message("bin dir: ${PROJECT_BINARY_DIR}")

add_compile_options(-std=c++11 -g -O0 -w)

#file(GLOB_RECURSE src_list ${PROJECT_SOURCE_DIR} *.cpp *.c) # old way, dangerous
#file(GLOB_RECURSE REMOVE_CMAKE ${PROJECT_BINARY_DIR}/*)
#list(REMOVE_ITEM src_list ${REMOVE_CMAKE})
file(GLOB src_list ${PROJECT_SOURCE_DIR} *.cpp *.c)
add_executable(${PROJECT_NAME} ${src_list})
set(INSTALL_HEADERS ${PROJECT_SOURCE_DIR}/binary_search_tree.h)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES ${INSTALL_HEADERS} DESTINATION include)
