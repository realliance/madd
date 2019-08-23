set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
    PRIVATE
        "${DIR}/texturecomponent.h"
        "${DIR}/shadercomponent.h"
        "${DIR}/vertexarraycomponent.h"
        "${DIR}/renderedcomponent.h"
)
target_include_directories(madd PRIVATE "${DIR}")
