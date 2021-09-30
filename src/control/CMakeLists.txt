include_directories(${CMAKE_SOURCE_DIR})

set(SOURCE_FILES	qtControlUnit.cpp)

add_library				(control ${SOURCE_FILES})
target_link_libraries	(control Qt5::Core
								 Qt5::Widgets)
target_compile_options	(control PRIVATE -fPIC)		