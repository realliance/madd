add_subdirectory(assets)
add_subdirectory(systems)
add_subdirectory(components)
set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
    PRIVATE
        "${DIR}/camerasystem.h"
        "${DIR}/madd.h"
        "${DIR}/errors.h"
        "${DIR}/util.h"
)
target_include_directories(madd PRIVATE "${madd_SOURCE_DIR}/include")
