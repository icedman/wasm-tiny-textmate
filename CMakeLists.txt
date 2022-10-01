cmake_minimum_required(VERSION 3.0)

project(app)

add_definitions(-Os)
add_definitions(-s)

add_subdirectory("./lib")

file(GLOB sourceFiles ./syntax_highlight.c)

add_executable(syntax_highlight ${sourceFiles})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Os -s WASM=1 -s INITIAL_MEMORY=33554432 -s ALLOW_MEMORY_GROWTH=1")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s WASM=1 -s INITIAL_MEMORY=33554432 -s ALLOW_MEMORY_GROWTH=1")

target_link_libraries(syntax_highlight c_lib)
