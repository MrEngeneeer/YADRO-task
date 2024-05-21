cmake_minimum_required(VERSION 3.22)
project(YADRO)

set(CMAKE_CXX_STANDARD 20)


add_executable(YADRO main.cpp
        TapeController/FileTapeController.cpp
        TapeController/FileTapeController.h
        Sorter/Sorter.cpp
        Sorter/Sorter.h
        TapeController/FileTapeController.cpp
        TapeController/FileTapeController.cpp
)
