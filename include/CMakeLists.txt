add_subdirectory(assets)
add_subdirectory(systems)
set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
    PRIVATE
        "${DIR}/camera.h"
        "${DIR}/gameobject.h"
        "${DIR}/madd.h"
        "${DIR}/errors.h"
        "${DIR}/util.h"
)
target_include_directories(madd PRIVATE "${madd_SOURCE_DIR}/include")
