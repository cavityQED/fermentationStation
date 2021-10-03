include_directories(${CMAKE_SOURCE_DIR})

add_library(common qtCommon.cpp)
target_link_libraries(common Qt5::Core Qt5::Widgets)
target_compile_options(common PRIVATE -fPIC)