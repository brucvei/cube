cmake_minimum_required(VERSION 3.25)
project(cube C)

set(CMAKE_C_STANDARD 11)
set(libs "../../../../usr/include")

include_directories(SYSTEM /usr/include/ )
include_directories(${libs})

set(SOURCE_FILES
        cube.c
        ${libs}/string.h
        ${libs}/unistd.h
        ${libs}/math.h
        )

add_executable(cube ${SOURCE_FILES})
target_link_libraries(cube m)