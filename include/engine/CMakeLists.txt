target_sources(madd
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/camera.h"
        "${CMAKE_CURRENT_LIST_DIR}/gameobject.h"
        "${CMAKE_CURRENT_LIST_DIR}/madd.h"
        "${CMAKE_CURRENT_LIST_DIR}/shader.h"
        "${CMAKE_CURRENT_LIST_DIR}/shaderprogram.h"
        "${CMAKE_CURRENT_LIST_DIR}/texture.h"
        "${CMAKE_CURRENT_LIST_DIR}/uniform.h"
        "${CMAKE_CURRENT_LIST_DIR}/vertexarray.h"
        "${CMAKE_CURRENT_LIST_DIR}/renderedobject.h"
)
target_include_directories(madd PRIVATE "${madd_SOURCE_DIR}/include/engine")