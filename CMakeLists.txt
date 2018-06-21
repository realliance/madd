cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
project(madd)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -Werror -pedantic -g")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${madd_SOURCE_DIR})


add_executable(madd "")
add_subdirectory(src)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
set(CMAKE_STATIC_LINKER_FLAGS "-lGL -lX11 -lpthread -lXrandr -lXi")
target_link_libraries(madd ${GLFW_LIBRARIES} ${CMAKE_DL_LIBS})
