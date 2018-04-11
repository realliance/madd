#version 330 core
#define M_PI 3.1415926535897932384626433832795
out vec4 FragColor;

uniform float time;

void main() {
  FragColor = vec4(sin(time) + 0.5f, 0.5f, 0.5f, 1.0f);
}
