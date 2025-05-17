cmake_minimum_required(VERSION 3.8)

# set(CMAKE_C_COMPILER "gcc")
# set(CMAKE_CXX_COMPILER "g++")

project("determinism_test")

include_directories(include)
file(GLOB_RECURSE SOURCES
    "src/determinism_test.c"
    "src/cases.c"
    "src/math/*.c"
)

add_executable(${PROJECT_NAME} ${SOURCES})

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /fp:precise /Ox /Oi- /wd4244)
    message("MSVC set")
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -ffp-model=strict)
    message("CLANG set")
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE -O2 -fexcess-precision=standard -ffp-contract=off)
    message("gcc set")
endif()   
