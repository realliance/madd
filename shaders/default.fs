#version 330 core
#define M_PI 3.1415926535897932384626433832795
out vec4 FragColor;
in vec3 ourColor;

uniform float time;

void main() {
  FragColor = vec4(ourColor, 1.0f);
}
