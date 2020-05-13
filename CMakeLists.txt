cmake_minimum_required(VERSION 3.5)

project(qgit LANGUAGES CXX)

add_definitions(-DCMAKE_VERSION_MAJOR=0)
add_definitions(-DCMAKE_VERSION_MINOR=0)
add_definitions(-DCMAKE_VERSION_PATCH=0)

include_directories(src/headers)
file(GLOB CMAKE_CXX_SOURCES src/*.cpp src/**/*.cpp)
file(GLOB CMAKE_CXX_HEADERS src/headers/*.h src/headers/**/*.h)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

qt5_wrap_cpp(CMAKE_CXX_SOURCES ${CMAKE_CXX_HEADERS})
add_executable(qgit ${CMAKE_CXX_SOURCES})
target_link_libraries(qgit Qt5::Core)
