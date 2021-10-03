include_directories(${CMAKE_SOURCE_DIR})
set(SOURCE_FILES	qtControlUnit.cpp)

add_library(control qtControlUnit.cpp )#${CMAKE_SOURCE_DIR}/../include/control/qtControlUnit.h)
target_link_libraries(control Qt5::Widgets
							  Qt5::Core)
target_compile_options(control PRIVATE -fPIC)		