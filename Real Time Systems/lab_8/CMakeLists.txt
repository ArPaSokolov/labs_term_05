cmake_minimum_required(VERSION 3.10)

project(LockFreeStack)

set(CMAKE_CXX_STANDARD 17)

add_library(LockFreeVersionedStack INTERFACE)

target_include_directories(LockFreeVersionedStack INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(lab_8 LockFreeStack.cpp)

target_link_libraries(lab_8 LockFreeVersionedStack)
