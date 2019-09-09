set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
    PRIVATE
      "${DIR}/rendersystem.h"
      "${DIR}/shadersystem.h"
      "${DIR}/texturesystem.h"
      "${DIR}/meshsystem.h"
)
target_include_directories(madd PRIVATE "${DIR}")
