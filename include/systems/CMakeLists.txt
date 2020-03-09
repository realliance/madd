set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
    PRIVATE
      "${DIR}/keyboardeventsystem.h"
      "${DIR}/mouseeventsystem.h"
      "${DIR}/collider.h"
      "${DIR}/rendersystem.h"
      "${DIR}/shadersystem.h"
      "${DIR}/texturesystem.h"
      "${DIR}/meshsystem.h"
      "${DIR}/camerasystem.h"
      "${DIR}/glfwsystem.h"
      "${DIR}/instancerendersystem.h"
      "${DIR}/freecamsystem.h"
)
target_include_directories(madd PRIVATE "${DIR}")
