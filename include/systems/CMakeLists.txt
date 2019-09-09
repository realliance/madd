set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
    PRIVATE
      "${DIR}/system.h"
      "${DIR}/keycodes.h"
      "${DIR}/keyboardeventsystem.h"
      "${DIR}/mouseeventsystem.h"
      "${DIR}/collider.h"
      "${DIR}/rendersystem.h"
      "${DIR}/shadersystem.h"
      "${DIR}/texturesystem.h"
      "${DIR}/meshsystem.h"
      "${DIR}/camerasystem.h"
      "${DIR}/windowsystem.h"
)
target_include_directories(madd PRIVATE "${DIR}")
