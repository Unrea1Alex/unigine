cmake_minimum_required(VERSION 3.5)

project(domain LANGUAGES CXX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -pthread")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC
     "*.h"
	 "*.cpp" 
)

add_executable(domain ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE tbb)