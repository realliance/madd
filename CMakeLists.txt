cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
project(madd)

find_package(PkgConfig)

#if(PKGCONFIG_FOUND)
#	pkg_search_module(GLFW REQUIRED glfw3)
#	pkg_search_module(GLM REQUIRED glm)
#elseif(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/config.cmake)
#	file(WRITE
#			"${CMAKE_CURRENT_BINARY_DIR}/config.cmake" 
#				"#SET THE GLFWPREFIX VARIABLE TO YOUR GLFW FOLDER\n"
#				"set(GLFWPREFIX GLFW_DIR_HERE)\n"
#				"#SET THE GLMPREFIX VARIABLE TO YOUR GLM FOLDER\n"
#				"set(GLMPREFIX GLM_DIR_HERE)\n\n"
#				"set(GLFW_LIBDIR \${GLFWPREFIX}/lib)\n"
#				"set(GLFW_LDFLAGS -L\${GLFWPREFIX}/lib;-lglfw3)\n"
#				"set(GLFW_INCLUDEDIR \${GLFWPREFIX}/include)\n"
#				"set(GLFW_LIBRARIES glfw3)\n"
#				"set(GLM_INCLUDEDIR \${GLMPREFIX})\n"
#		)
#	MESSAGE(FATAL_ERROR "Set the PREFIX Variables in ${CMAKE_CURRENT_BINARY_DIR}/config.cmake")
#elseif(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/config.cmake)
#	include(${CMAKE_CURRENT_BINARY_DIR}/config.cmake)
#	if(${GLFWPREFIX} STREQUAL "GLFW_DIR_HERE")
#		MESSAGE(FATAL_ERROR "Set the GLFWPREFIX Variable in ${CMAKE_CURRENT_BINARY_DIR}/config.cmake")
#	endif()
#	if(${GLMPREFIX} STREQUAL "GLM_DIR_HERE")
#		MESSAGE(FATAL_ERROR "Set the GLMPREFIX Variable in ${CMAKE_CURRENT_BINARY_DIR}/config.cmake")
#	endif()
#endif()

set(GLFW_BUILD_EXAMPLES FALSE)
set(GLFW_BUILD_TESTS FALSE)
set(GLFW_BUILD_DOCS FALSE)
set(GLFW_BUILD_EXAMPLES FALSE PARENT_SCOPE )
set(GLFW_BUILD_TESTS FALSE PARENT_SCOPE )
set(GLFW_BUILD_DOCS FALSE PARENT_SCOPE )

add_subdirectory(libraries)
add_library(madd "")
add_subdirectory(${madd_SOURCE_DIR}/src)
add_subdirectory(${madd_SOURCE_DIR}/include)

if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT madd)
	set_target_properties(madd PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
	target_link_libraries(madd glfw)
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Werror -pedantic -g -static-libgcc -static-libstdc++ -ggdb")
	target_link_libraries(madd glfw ${CMAKE_DL_LIBS})
endif()

target_include_directories(madd PUBLIC ${GLFW_INCLUDEDIR})
target_include_directories(madd PUBLIC ${GLM_INCLUDEDIR})