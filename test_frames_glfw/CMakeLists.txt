cmake_minimum_required(VERSION 2.8)

project(test_frames)

# OpenGL
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
	include_directories(${OPENGL_INCLUDE_DIRS})
	link_libraries(${OPENGL_LIBRARIES})
endif()

# GLFW
add_subdirectory(glfw)

# glad
add_subdirectory(glad)

include_directories( 
	glfw/include
	glad/include
)

add_executable( test_frames
	main.cpp
)

set(LINK_LIBS glfw glad)
if(UNIX)
	set(LINK_LIBS ${LINK_LIBS} m dl pthread)
endif()
target_link_libraries( test_frames ${LINK_LIBS} )