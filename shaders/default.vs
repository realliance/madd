#version 330 core
#define M_PI 3.1415926535897932384626433832795
layout(location = 0) in vec3 aPos;

uniform float time;

void main() {
  gl_Position = vec4(aPos, 1.0);
}
