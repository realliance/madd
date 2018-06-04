include_directories(${madd_SOURCE_DIR}/include)
message("${MyProject_SOURCE_DIR}/include")
add_executable(madd glad.c game.cpp gameobject.cpp madd.cpp main.cpp shader.cpp shaderprogram.cpp vertexarray.cpp)
target_link_libraries(madd "C:/TDM-GCC-64/lib/libglfw3.a")