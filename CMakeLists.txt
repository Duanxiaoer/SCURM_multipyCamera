cmake_minimum_required(VERSION 3.8)
project(RM_LiveSys)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
add_executable(RM_LiveSys main.cpp System.h System.cpp  )
target_link_libraries(RM_LiveSys ${OpenCV_LIBS})