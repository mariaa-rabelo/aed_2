cmake_minimum_required(VERSION 3.26)
project(aed_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(aed_2
        src/main.cpp
        src/Airline.h
        src/Airline.cpp
        src/Airport.h
        src/Airport.cpp
        src/Graph.h
        src/FileReader.h
        src/FileReader.cpp
        src/Application.h
        src/Application.cpp
        src/Menu.h
        src/Menu.cpp)
