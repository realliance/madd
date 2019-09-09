set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
  PRIVATE
  "${DIR}/shadersystem.cpp"
  "${DIR}/texturesystem.cpp"
  "${DIR}/meshsystem.cpp"
  "${DIR}/rendersystem.cpp"
)
