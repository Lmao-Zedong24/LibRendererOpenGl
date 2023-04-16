#download GLFW directly online
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

#download Libmath
FetchContent_Declare(
	libMath 
	GIT_REPOSITORY ssh://git@git.isartintra.com:2424/2022/Lib_De_Math/Robin.git #LINK OF MY LIBMATH PUT YOURS CHANGE
	GIT_SHALLOW ON
)
set(BUILD_UNIT_TEST OFF) #remove this

#get source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cc # C with classe
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.cxx
	${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
	
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Header)
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES} ${SOURCE_FILES})#generate tree folders

#create vs project
FetchContent_MakeAvailable(GLFW libMath)
set(PROJECT_NAME ModernOpenGLProject) #CHANGE

add_executable(${PROJECT_NAME}) #set le nom du projet
#set les lib exterieur
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}\\Include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}\\dependencies\\GLAD) #you need to create the folder
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_SOURCE_DIR}\\include)
target_include_directories(${PROJECT_NAME} PRIVATE ${libmath_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE LibMath)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

target_sources(${PROJECT_NAME} PRIVATE ${HEADER_FILES} ${SOURCE_FILES})
target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}\\dependencies\\GLAD\\glad\\glad.c)

#copy les dlls
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
  COMMAND_EXPAND_LISTS
)
set(PROJECT_NAME ${PROJECT_NAME} PARENT_SCOPE) #to send the project name to the parent