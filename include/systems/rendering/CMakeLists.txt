set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
    PRIVATE
      "${DIR}/renderedobject.h"
      "${DIR}/rendersystem.h"
      "${DIR}/shaderprogram.h"
      "${DIR}/texture.h"
      "${DIR}/vertexarray.h"
)
target_include_directories(madd PRIVATE "${DIR}")
