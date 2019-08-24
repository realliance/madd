add_subdirectory(event)
add_subdirectory(rendering)
add_subdirectory(physics)
set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
    PRIVATE
      "${DIR}/system.h"
)
target_include_directories(madd PRIVATE "${DIR}")
