set(SOURCE_FILES	qtServer.cpp)

add_library				(network ${SOURCE_FILES})
target_compile_options	(network PRIVATE -fPIC)