cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(SPD_Lab2 VERSION 0.1 LANGUAGES CXX)

file(GLOB_RECURSE HEADERS inc/*.hh)
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(Lab2)

target_sources(Lab2 PRIVATE
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(Lab2 PRIVATE inc)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Lab2 PRIVATE 
    -g
    -Wall
    -Wextra
    -pedantic
    -Werror=return-type
    -Werror=parentheses
    -Werror=vla
    -Werror=array-bounds
    -Wcast-qual
    -Wmaybe-uninitialized
)
endif() 
