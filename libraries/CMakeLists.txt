
FetchContent_Declare(
  stb

	GIT_REPOSITORY https://github.com/nothings/stb
	URL_HASH f54acd4e13430c5122cab4ca657705c84aa61b08
)
FetchContent_MakeAvailable(stb)
target_include_directories(madd PRIVATE ${stb_SOURCE_DIR})

set(GLAD_PROFILE "core")
set(GLAD_API "gl=4.3")
set(GLAD_EXTENSIONS "GL_KHR_debug")


FetchContent_Declare(
  glad

  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
	GIT_TAG        v0.1.27
)

FetchContent_MakeAvailable(glad)