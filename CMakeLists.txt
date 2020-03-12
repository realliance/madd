cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
project(madd)
include(FetchContent)

find_package(PkgConfig)

add_library(madd "")
add_subdirectory(${madd_SOURCE_DIR}/libraries)
add_subdirectory(${madd_SOURCE_DIR}/include)
add_subdirectory(${madd_SOURCE_DIR}/src)

target_link_libraries(madd 
	PUBLIC 
		glad 
		glfw 
	PRIVATE 
		${CMAKE_DL_LIBS}
)

target_include_directories(madd INTERFACE "${madd_SOURCE_DIR}/include")
target_include_directories(madd INTERFACE "${madd_SOURCE_DIR}/include/systems")
