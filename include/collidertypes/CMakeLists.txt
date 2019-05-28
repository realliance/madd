set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
    PRIVATE
        "${DIR}/boxcollider.h"
        "${DIR}/spherecollider.h"
)
target_include_directories(madd PRIVATE "${madd_SOURCE_DIR}/include")
