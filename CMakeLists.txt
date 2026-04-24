cmake_minimum_required(VERSION 3.10)

project(AniMon)

set(CMAKE_CXX_STANDARD 17)

# Main executable
add_executable(AniMon
    src/main.cpp
    src/AsciiPrinter.cpp
    src/Character.cpp 
    src/Monster.cpp
    src/Item.cpp
    src/CaveFactory.cpp
)

target_include_directories(AniMon PUBLIC include)