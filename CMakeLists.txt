cmake_minimum_required(VERSION 3.10.2)
project(zxProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(zxProject1 main.cpp base/ReadData.cpp base/ReadData.h base/Utils.h base/Utils.cpp base/WriteData.cpp
        base/WriteData.h Draw.h Draw.cpp)
#add_executable(zxProject2 testDraw.cpp base/ReadData.cpp base/ReadData.h base/Utils.h base/Utils.cpp base/WriteData.cpp
       # base/WriteData.h Draw.h Draw.cpp)

target_link_libraries(zxProject1 GL GLU glut)