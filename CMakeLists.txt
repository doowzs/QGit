cmake_minimum_required(VERSION 3.5)

project(QGit LANGUAGES CXX)

add_definitions(-DCMAKE_VERSION_MAJOR=0)
add_definitions(-DCMAKE_VERSION_MINOR=0)
add_definitions(-DCMAKE_VERSION_PATCH=0)

include_directories(src/headers src/3rdparty)
file(GLOB CMAKE_CXX_SOURCES src/*.cpp src/**/*.cpp src/3rdparty/**/*.cpp)
file(GLOB CMAKE_CXX_HEADERS src/headers/*.h src/headers/**/*.h src/3rdparty/**/*.h)
file(GLOB CMAKE_CXX_RESOURCES src/resources/*.qrc)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})

qt5_wrap_cpp(CMAKE_CXX_SOURCES ${CMAKE_CXX_HEADERS})
qt5_add_resources(CMAKE_CXX_SOURCES ${CMAKE_CXX_RESOURCES})
add_executable(QGit ${CMAKE_CXX_SOURCES})
target_link_libraries(QGit Qt5::Core Qt5::Widgets ${ZLIB_LIBRARIES})
