cmake_minimum_required(VERSION 3.10)

project(AniMon)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 REQUIRED COMPONENTS Sql)

# Main executable
add_executable(AniMon
    src/main.cpp
    src/AsciiPrinter.cpp
    src/Character.cpp 
    src/Monster.cpp
    src/Item.cpp
    src/CaveFactory.cpp
    src/Database.cpp
)

target_include_directories(AniMon PUBLIC include)

target_link_libraries(AniMon PRIVATE Qt5::Sql)