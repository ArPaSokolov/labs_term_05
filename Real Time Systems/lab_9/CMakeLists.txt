cmake_minimum_required(VERSION 3.15)
project(lab_9_server)
# project(lab_9_client)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_9_server TCP_server.cpp)
# add_executable(lab_9_client TCP_client.cpp)
# add_executable(lab_9_server UDP_server.cpp)
# add_executable(lab_9_client UDP_client.cpp)