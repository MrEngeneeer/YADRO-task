cmake_minimum_required(VERSION 3.22)
project(YADRO)

set(CMAKE_CXX_STANDARD 20)

set(nlohmann_json_DIR "C:/Users/iRU/.vcpkg-clion/vcpkg/installed/x64-mingw-dynamic/share/nlohmann_json")

add_executable(YADRO main.cpp
        TapeController/FileTapeController.cpp
        TapeController/FileTapeController.h
        Sorter/Sorter.cpp
        Sorter/Sorter.h
        TapeController/FileTapeController.cpp
        TapeController/FileTapeController.cpp
)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(YADRO PRIVATE nlohmann_json::nlohmann_json)
