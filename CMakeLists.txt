cmake_minimum_required(VERSION 3.8)

# set(CMAKE_C_COMPILER "gcc")
# set(CMAKE_CXX_COMPILER "g++")

project("determinism_test")

file(GLOB_RECURSE SOURCES
    "src/determinism_test.c"
    "src/cases.c"
    "src/math/*.c"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /Ox /Oi- /wd4244 /wd4723 /wd4146)
    message("MSVC set")
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -O2 -fexcess-precision=standard -ffp-contract=off)
    message("GCC/Clang set")
endif()   
