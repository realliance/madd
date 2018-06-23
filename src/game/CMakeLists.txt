set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
    PRIVATE
        "${DIR}/game.cpp"
        "${DIR}/main.cpp"
        "${DIR}/cube.cpp"
)
target_include_directories(madd PRIVATE "${madd_SOURCE_DIR}/include/game")