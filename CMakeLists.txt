cmake_minimum_required(VERSION 3.8)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

project("determinism_test")

include_directories(include)
file(GLOB_RECURSE SOURCES
    "src/determinism_test.c"
    "src/math/*.c"
)

add_executable(${PROJECT_NAME} ${SOURCES})

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /fp:strict /Od)
    message("MSVC set")
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -ffp-model=strict)
    message("CLANG set")
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    message("gcc set")
endif()   
