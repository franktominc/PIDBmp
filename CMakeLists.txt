cmake_minimum_required(VERSION 3.5)
project(PID)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp FileHeader.cpp FileHeader.h InfoHeader.cpp InfoHeader.h helpers.cpp BitmapImage.cpp BitmapImage.h ColorPallete.cpp ColorPallete.h Bitmap.cpp Bitmap.h)
add_executable(PID ${SOURCE_FILES})