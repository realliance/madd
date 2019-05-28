set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CMAKE_BUILD_TYPE RELEASE FORCE)
add_subdirectory(glfw)

include("glad/glad/CMakeLists.txt")
set(LIBRARY_INCLUDES
		"${madd_SOURCE_DIR}/libraries/glm"
		"${madd_SOURCE_DIR}/libraries/glfw/include"
		"${madd_SOURCE_DIR}/libraries/KHR"
		"${madd_SOURCE_DIR}/libraries/stb"
		"${madd_SOURCE_DIR}/libraries/glad"
	PARENT_SCOPE)
