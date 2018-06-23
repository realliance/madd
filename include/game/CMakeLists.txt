set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
    PRIVATE
		"${DIR}/game.h"
        "${DIR}/main.h"
        "${DIR}/cube.h"
)
target_include_directories(madd PRIVATE "${madd_SOURCE_DIR}/include/game")