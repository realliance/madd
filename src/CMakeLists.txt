add_subdirectory(assets)
add_subdirectory(systems)
set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
    PRIVATE
        "${DIR}/camera.cpp"
        "${DIR}/madd.cpp"
        "${DIR}/util.cpp"
)
