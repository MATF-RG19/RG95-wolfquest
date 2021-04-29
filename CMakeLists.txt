cmake_minimum_required(VERSION 3.16)

project(wolfQuest)

add_subdirectory(textures)

add_executable(wolfQuest wolfQuest.cpp drawings/drawFunc.cpp drawings/drawFunc.hpp other/handy.cpp other/handy.hpp textures/image.cpp textures/image.hpp) 

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(wolfQuest ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} texture_lib)