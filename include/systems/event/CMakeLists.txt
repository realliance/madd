set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
    PRIVATE
        "${DIR}/keycodes.h"
        "${DIR}/eventhandler.h"
)
target_include_directories(madd PRIVATE "${DIR}")
