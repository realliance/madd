target_sources(madd
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/game.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/cube.cpp"
)
target_include_directories(madd PRIVATE "${madd_SOURCE_DIR}/include/game")