cmake_minimum_required(VERSION 3.9)
project(RM_LiveSys)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
add_executable(RM_LiveSys main.cpp System.h System.cpp RMVideoCapture.hpp RMVideoCapture.cpp )
target_link_libraries(RM_LiveSys ${OpenCV_LIBS})