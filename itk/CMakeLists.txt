cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Debug)
 
project(main)
 
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(main main3.cxx)

target_link_libraries(main ${ITK_LIBRARIES})
