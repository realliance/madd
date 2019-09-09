set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(madd
    PRIVATE
    "${DIR}/camerasystem.cpp"
    "${DIR}/shadersystem.cpp"
    "${DIR}/texturesystem.cpp"
    "${DIR}/meshsystem.cpp"
    "${DIR}/rendersystem.cpp"
    "${DIR}/collider.cpp"
    "${DIR}/keyboardeventsystem.cpp"
    "${DIR}/mouseeventsystem.cpp"
)