add_subdirectory(assets)
set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
    PRIVATE
        "${DIR}/camera.h"
        "${DIR}/gameobject.h"
        "${DIR}/madd.h"
        "${DIR}/shader.h"
        "${DIR}/shaderprogram.h"
        "${DIR}/texture.h"
        "${DIR}/vertexarray.h"
        "${DIR}/renderedobject.h"
        "${DIR}/eventhandler.h"
        "${DIR}/keycodes.h"
        "${DIR}/errors.h"
)
target_include_directories(madd PRIVATE "${madd_SOURCE_DIR}/include")