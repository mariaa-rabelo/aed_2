cmake_minimum_required(VERSION 3.26)
project(airports)

set(CMAKE_CXX_STANDARD 14)

add_executable(airports
        main.cpp
        Airline.h
        Airline.cpp
        Airport.h
        Airport.cpp
        Graph.h
        FileReader.h
        FileReader.cpp
        Application.h
        Application.cpp
        Menu.h
        Menu.cpp
        FlightOption.h
        FlightOption.cpp)
