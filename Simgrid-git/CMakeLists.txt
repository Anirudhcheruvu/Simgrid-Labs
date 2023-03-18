cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SimGridTemplateProject) # TODO: give a real name to your project here

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(SimGrid 3.27 REQUIRED) # This template requires SimGrid v3.27 because we use templated get()

include_directories(${SimGrid_INCLUDE_DIR})

add_executable(ping-pong ping-pong.cpp)
target_link_libraries(ping-pong ${SimGrid_LIBRARY})

add_executable(master-workers master-workers.cpp)
target_link_libraries(master-workers ${SimGrid_LIBRARY})

add_executable(master-workers-lab1 master-workers-lab1.cpp)
target_link_libraries(master-workers-lab1 ${SimGrid_LIBRARY})

add_executable(master-workers-lab2 master-workers-lab2.cpp)
target_link_libraries(master-workers-lab2 ${SimGrid_LIBRARY})

add_executable(master-workers-lab3 master-workers-lab3.cpp)
target_link_libraries(master-workers-lab3 ${SimGrid_LIBRARY})

add_executable(master-workers-lab4 master-workers-lab4.cpp)
target_link_libraries(master-workers-lab4 ${SimGrid_LIBRARY})

add_executable(master-workers-lab4-1 master-workers-lab4-1.cpp)
target_link_libraries(master-workers-lab4-1 ${SimGrid_LIBRARY})

add_executable(master-workers-lab4-2 master-workers-lab4-2.cpp)
target_link_libraries(master-workers-lab4-2 ${SimGrid_LIBRARY})

add_executable(master-workers-lab4-3 master-workers-lab4-3.cpp)
target_link_libraries(master-workers-lab4-3 ${SimGrid_LIBRARY})

add_executable(master-workers-lab5 master-workers-lab5.cpp)
target_link_libraries(master-workers-lab5 ${SimGrid_LIBRARY})

