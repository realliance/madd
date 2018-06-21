target_sources(madd
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/gameobject.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/madd.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/shader.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/shaderprogram.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/uniform.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/vertexarray.cpp"
)
target_include_directories(madd PRIVATE "${madd_SOURCE_DIR}/include/engine")