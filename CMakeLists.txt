cmake_minimum_required(VERSION 2.8)
project(GameOfLife)

set(EXECUTABLE_NAME "GameOfLife")

#Set path to Find scripts
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")

#Dependencies searching
find_package(SFML 2.3 COMPONENTS system window graphics REQUIRED)
find_package(Boost 1.57 COMPONENTS program_options REQUIRED)
find_package(Threads REQUIRED)

#Set the include directory of the project
include_directories(
	${GameOfLife_SOURCE_DIR}/include
	${SFML_INCLUDE_DIR}
	${Boost_INCLUDE_DIRS}
	)


#Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -Wall -Wextra -pedantic -pedantic-errors -Wnon-virtual-dtor -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Winline -Wunreachable-code -Wmissing-declarations")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

#Set a variable with all needed libraries
set(EXTERNAL_LIBRARIES
	${SFML_LIBRARIES}
	${Boost_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
	)

#Place the executable files in the root directory instead of in src
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src)

