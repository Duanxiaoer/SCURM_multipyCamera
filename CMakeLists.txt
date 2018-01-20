cmake_minimum_required(VERSION 3.5)
project(RM)

set(CMAKE_CXX_STANDARD 11)


find_package(OpenCV REQUIRED)
set(SOURCE_FILES main.cpp camera.cpp camera.h)
add_executable(RM ${SOURCE_FILES})
target_link_libraries(RM ${OpenCV_LIBS})