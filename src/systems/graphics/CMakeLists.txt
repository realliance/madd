set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
  PRIVATE
  "${DIR}/shader.cpp"
  "${DIR}/shaderprogram.cpp"
  "${DIR}/texture.cpp"
  "${DIR}/vertexarray.cpp"
  "${DIR}/renderedobject.cpp"
  "${DIR}/renderer.cpp"
)
