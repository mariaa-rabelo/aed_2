cmake_minimum_required(VERSION 3.26)
project(aed_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(aed_2
        src/main.cpp
        src/Airline.h
        src/Flight.h
        src/Airport.h
        src/Graph.h
        src/FileReader.h
        src/FileReader.cpp
        src/Application.cpp
        src/Application.h src/Airport.cpp)
