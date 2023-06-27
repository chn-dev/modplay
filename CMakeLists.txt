cmake_minimum_required(VERSION 2.8.4)

project(modplay)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB_RECURSE LIBMODPLAY_SOURCE_FILES src/modplay/*.c)
file(GLOB_RECURSE LIBMODPLAY_HEADER_FILES src/modplay/*.h)
add_library(modplay STATIC ${LIBMODPLAY_SOURCE_FILES} ${LIBMODPLAY_HEADER_FILES})

#SET(APP_EXE player)


add_executable(player src/player.c)
target_link_libraries(player ${SDL2_LIBRARIES} modplay)
