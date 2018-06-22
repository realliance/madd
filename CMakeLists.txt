cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
project(madd)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${madd_SOURCE_DIR})

find_package(PkgConfig)

if(PKGCONFIG_FOUND)
	pkg_search_module(GLFW REQUIRED glfw3)
	
elseif(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/glfw3.cmake)
	file(WRITE
			"${CMAKE_CURRENT_BINARY_DIR}/glfw3.cmake" 
				"#SET THE PREFIX VARIABLE TO YOUR GLFW FOLDER\n"
				"set(PREFIX GLFW_DIR_HERE)\n\n"
				"set(GLFW_LIBDIR \${PREFIX}/lib)\n"
				"set(GLFW_LDFLAGS -L\${PREFIX}/lib;-lglfw3)\n"
				"set(GLFW_INCLUDEDIR \${PREFIX}/include)\n"
				"set(GLFW_LIBRARIES glfw3)\n"
		)
	MESSAGE(FATAL_ERROR "Set the PREFIX Variable in ${CMAKE_CURRENT_BINARY_DIR}/glfw3.cmake")
	
elseif(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/glfw3.cmake)
	include(${CMAKE_CURRENT_BINARY_DIR}/glfw3.cmake)
	if(${PREFIX} STREQUAL "GLFW_DIR_HERE")
		MESSAGE(FATAL_ERROR "Set the PREFIX Variable in ${CMAKE_CURRENT_BINARY_DIR}/glfw3.cmake")
	endif()
endif()

link_directories(${GLFW_LIBDIR})
add_executable(madd "")
add_subdirectory(src)
add_subdirectory(include)

if (MSVC)
	target_link_libraries(madd ${GLFW_LIBRARIES})
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Werror -pedantic -g")
	target_link_libraries(madd ${GLFW_LDFLAGS} ${CMAKE_DL_LIBS})
endif()

target_include_directories(madd PUBLIC ${GLFW_INCLUDEDIR})
