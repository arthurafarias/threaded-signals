cmake_minimum_required(VERSION 3.30)
project(threaded-signals-example-simple VERSION 0.1)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} threaded-signals)