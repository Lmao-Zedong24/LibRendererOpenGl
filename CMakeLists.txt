cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

#set version c++ to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(ModernOpenGLRender) #Set le nom de la solution
add_subdirectory(ModernOpenGL) #create or link to cmake subfolder (can't remeber)

if (MSVC)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()