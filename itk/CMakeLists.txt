cmake_minimum_required(VERSION 2.8)
 
project(main)
 
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(main main2.cxx)

target_link_libraries(main ${ITK_LIBRARIES})
