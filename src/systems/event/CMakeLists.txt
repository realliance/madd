set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
  PRIVATE
  "${DIR}/eventhandler.cpp"
  "${DIR}/keyboardeventsystem.cpp"
  "${DIR}/mouseeventsystem.cpp"
)
