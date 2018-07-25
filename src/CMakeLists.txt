add_subdirectory(assets)
set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
    PRIVATE
        "${DIR}/camera.cpp"
        "${DIR}/madd.cpp"
        "${DIR}/shader.cpp"
        "${DIR}/shaderprogram.cpp"
        "${DIR}/texture.cpp"
        "${DIR}/vertexarray.cpp"
        "${DIR}/renderedobject.cpp"
        "${DIR}/renderer.cpp"
        "${DIR}/eventhandler.cpp"
)
target_include_directories(madd PRIVATE "${madd_SOURCE_DIR}/include")
