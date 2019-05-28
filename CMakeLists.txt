cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
project(madd)

find_package(PkgConfig)

add_library(madd "")
add_subdirectory(${madd_SOURCE_DIR}/src)
add_subdirectory(${madd_SOURCE_DIR}/include)
add_subdirectory(${madd_SOURCE_DIR}/libraries)

if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT madd)
	set_target_properties(madd PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
	target_link_libraries(madd glfw)
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Werror -pedantic -g -static-libgcc -static-libstdc++ -ggdb")
	target_link_libraries(madd glfw ${CMAKE_DL_LIBS})
endif()

target_include_directories(madd PUBLIC ${LIBRARY_INCLUDES})
