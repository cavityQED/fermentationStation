include_directories(${CMAKE_SOURCE_DIR})
set(SOURCE_FILES	qtControlUnit.cpp
					qtControlCell.cpp
					qtControlStation.cpp)

add_library(control ${SOURCE_FILES})
target_link_libraries(control Qt5::Widgets
							  Qt5::Core)
target_compile_options(control PRIVATE -fPIC)		