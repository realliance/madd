set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
  PRIVATE
  # "${DIR}/meshcollidercomponent.cpp"
  "${DIR}/texturecomponent.cpp"
  "${DIR}/shadercomponent.cpp"
  "${DIR}/meshcomponent.cpp"
  "${DIR}/renderedcomponent.cpp"
  "${DIR}/cameracomponent.cpp"
  "${DIR}/keyboardeventcomponent.cpp"
  "${DIR}/mouseeventcomponent.cpp"
  "${DIR}/windowcomponent.cpp"
  "${DIR}/freecamcomponent.cpp"
  "${DIR}/instancerenderedcomponent.cpp"
)
