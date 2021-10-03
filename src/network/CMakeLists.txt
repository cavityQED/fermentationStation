set(SOURCE_FILES	qtServer.cpp)

include_directories(${CMAKE_SOURCE_DIR})

add_library(network ${SOURCE_FILES})
target_link_libraries(network control)
target_compile_options(network PRIVATE -fPIC)