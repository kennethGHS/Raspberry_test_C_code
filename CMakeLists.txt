cmake_minimum_required(VERSION 3.17)
project(ImageTest C)

set(CMAKE_C_STANDARD 99)

add_executable(ImageTest main.c Code/ImageGet.c Code/ImageGet.h Code/IOManagement.h Code/IOManagement.c Code/ManualGPIO.h Code/ManualGPIO.c Code/Monitoring.c Code/Monitoring.h)