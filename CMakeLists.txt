cmake_minimum_required(VERSION 2.8.4)

project(modplay)

find_package(SDL2 REQUIRED)
#find_library(MATH_LIBRARY m)
#if(NOT MATH_LIBRARY)
#   set( MATH_LIBRARY "" )
#endif()

include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCE_FILES src/*.c)
file(GLOB_RECURSE HEADER_FILES src/*.h)

add_executable(modplay ${HEADER_FILES} ${SOURCE_FILES})
#target_link_libraries(Aliasing ${SDL2_LIBRARIES} ${MATH_LIBRARY})
target_link_libraries(modplay ${SDL2_LIBRARIES})
