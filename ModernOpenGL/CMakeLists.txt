
# set the project name
get_filename_component(CURRENT_FOLDER_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
set(PROJECT_NAME ${CURRENT_FOLDER_NAME})

include(FetchContent)
FetchContent_Declare(
	GLFW 
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 3.3.8
	GIT_SHALLOW ON #.lib if OFF .dll if ON
)
set(BUILD_SHARED_LIBS ON) #explication on teams
set(GLFW_INSTALL OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)

FetchContent_MakeAvailable(GLFW)

#download Libmath
FetchContent_Declare(
	libMath 
	GIT_REPOSITORY https://github.com/Lmao-Zedong24/LibMath.git #LINK OF MY LIBMATH PUT YOURS CHANGE
	GIT_TAG main
	GIT_SHALLOW ON
)
set(BUILD_UNIT_TEST OFF) #remove this

FetchContent_MakeAvailable(libMath)


###############################
#                             #
# Sources                     #
#                             #
###############################

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cc # C with classe
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.cxx
	${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
	
# Add header files
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES} ${SOURCE_FILES})

message (${CMAKE_CURRENT_SOURCE_DIR})
###############################
#                             #
# Executable                  #
#                             #
###############################

add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})
include_directories(${PROJECT_INCLUDE_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}\\Include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}\\dependencies\\GLAD) #you need to create the folder
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_SOURCE_DIR}\\include)
target_include_directories(${PROJECT_NAME} PRIVATE ${libmath_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE LibMath)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

set(PROJECT_NAME ${PROJECT_NAME} PARENT_SCOPE)