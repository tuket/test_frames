cmake_minimum_required(VERSION 2.8)

project(test_frames)

# OpenGL
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
	include_directories(${OPENGL_INCLUDE_DIRS})
	link_libraries(${OPENGL_LIBRARIES})
endif()

# SDL2
add_subdirectory(SDL2)

# glad
add_subdirectory(glad)

include_directories( 
	SDL2/include
	glad/include
)

add_executable( test_frames
	main.cpp
)

set(LINK_LIBS SDL2-static SDL2main glad)
if(UNIX)
	set(LINK_LIBS ${LINK_LIBS} m dl pthread)
endif()
target_link_libraries( test_frames ${LINK_LIBS} )