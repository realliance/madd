set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
  PRIVATE
  "${DIR}/shaderprogram.cpp"
  "${DIR}/texture.cpp"
  "${DIR}/vertexarray.cpp"
  "${DIR}/renderedobject.cpp"
  "${DIR}/rendersystem.cpp"
)
