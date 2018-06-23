#version 330 core
#define M_PI 3.1415926535897932384626433832795
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform float time;
uniform mat4 transform;
out vec3 ourColor;
out vec2 TexCoord;

void main() {
  gl_Position = transform * vec4(aPos, 1.0f);
  ourColor = aColor;
  TexCoord = aTexCoord;
}
