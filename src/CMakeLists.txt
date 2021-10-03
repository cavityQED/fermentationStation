cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_STANDARD 20)
project(fermentation)

include_directories(/home/mike/projects/asio_networking/asio-1.18.2/include)
include_directories(/home/mike/projects/asio_networking/src/common)
include_directories(/usr/include/x86_64-linux-gnu/qt5)
include_directories(/usr/include/x86_64-linux-gnu/qt5/QtCore)
include_directories(/usr/include/x86_64-linux-gnu/qt5/QtWidgets)
include_directories(${CMAKE_SOURCE_DIR})

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
if(Qt5Core_FOUND)
	message("qt found")
endif()

set(CMAKE_AUTOMOC ON)

add_subdirectory(common)
add_subdirectory(control)
add_subdirectory(network)

set(LINKED_LIBS	control network pthread)

add_library(fermentationStation libMain.cpp)
target_link_libraries(fermentationStation control network pthread)
target_compile_options(fermentationStation PRIVATE -fPIC)

add_executable(ferment main.cpp)
target_link_libraries(ferment fermentationStation)
target_compile_options(ferment PRIVATE -fPIC)
