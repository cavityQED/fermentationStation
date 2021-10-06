set(SOURCE_FILES	qtServer.cpp
					qtServerWindow.cpp)

include_directories(${CMAKE_SOURCE_DIR})

add_library(network ${SOURCE_FILES})
target_link_libraries(network control common)
target_compile_options(network PRIVATE -fPIC)