target_sources(madd
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/glad.c"
        "${CMAKE_CURRENT_LIST_DIR}/stb_image.cpp"
)
target_include_directories(madd PRIVATE "${madd_SOURCE_DIR}/include/libraries")