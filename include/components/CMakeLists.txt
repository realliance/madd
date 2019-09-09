set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
    PRIVATE
        "${DIR}/texturecomponent.h"
        "${DIR}/shadercomponent.h"
        "${DIR}/meshcomponent.h"
        "${DIR}/renderedcomponent.h"
        "${DIR}/cameracomponent.h"
        "${DIR}/component.h"
        "${DIR}/meshcollidercomponent.h"
        "${DIR}/collidercomponent.h"
        "${DIR}/keyboardeventcomponent.h"
        "${DIR}/mouseeventcomponent.h"
        "${DIR}/windowcomponent.h"
)
target_include_directories(madd PRIVATE "${DIR}")
