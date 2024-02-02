cmake_minimum_required(VERSION 3.26)
project(WarpWiggle C)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCE_FILES "src/*.c")
file(GLOB SOURCE_FILES_IN_SUBDIRECTORIES "src/*/*.c")
file(GLOB HEADER_FILES "include/*.h")
file(GLOB HEADER_FILES_IN_SUBDIRECTORIES "src/*/*.h")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${SOURCE_FILES_IN_SUBDIRECTORIES} ${HEADER_FILES} ${HEADER_FILES_IN_SUBDIRECTORIES})


INCLUDE(FindPkgConfig)

if(UNIX)
	pkg_search_module(SDL2 REQUIRED sdl2)
	pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
 
 	include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
    	target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
    
else ()
	list(APPEND CMAKE_MODULE_PATH ${CMAKE_SDL2_MODULES_PATH})
	find_package(SDL2 REQUIRED)
	find_package(SDL2_image REQUIRED)
  
	include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::Image)
endif ()
