cmake_minimum_required(VERSION 3.5)

project(cpp_multithreaded_folder_organizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_executable(mamamia main.cpp)
