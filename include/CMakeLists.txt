add_subdirectory(assets)
add_subdirectory(systems)
add_subdirectory(components)
set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
    PRIVATE
        "${DIR}/madd.h"
        "${DIR}/util.h"
)
target_include_directories(madd PRIVATE "${madd_SOURCE_DIR}/include")
