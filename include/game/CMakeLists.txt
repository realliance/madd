target_sources(madd
    PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/game.h"
        "${CMAKE_CURRENT_LIST_DIR}/main.h"
)
target_include_directories(madd PRIVATE "${madd_SOURCE_DIR}/include/game")