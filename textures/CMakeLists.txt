add_library(
    texture_lib
    image.cpp
    image.hpp
)
target_link_directories(texture_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")