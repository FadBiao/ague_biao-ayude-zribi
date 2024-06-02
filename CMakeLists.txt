cmake_minimum_required(VERSION 3.24.2)
project(projet_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(projet_cpp Main.cpp)



link_directories ("C:/Program Files/MySQL/Connector C++ 8.0/lib64/vs14")

# Include the MySQL Connector/C++ headers
