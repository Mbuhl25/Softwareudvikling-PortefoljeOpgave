cmake_minimum_required(VERSION 3.10)

# Project declaration 
project(PokemonRipOff)

# C++ standard for all targets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(PokemonRipOff main.cpp Character.cpp Monster.cpp AsciiPrinter.cpp)

# =============================================================================
# BUILD INSTRUCTIONS:
#   Gå ind i build mappen (opret den hvis den ikke findes)
#   cmake ..
#   make
#   ./clock
# =============================================================================