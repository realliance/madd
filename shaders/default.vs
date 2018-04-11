#version 330 core
layout(location = 0) in vec3 aPos;

uniform float time;

void main() {
  float t = time;
  float x = cos(t) - cos((1 + t) * t);
  float y = sin(t) - sin((1 + t) * t);
  x = (aPos.x / 4)+ x / 4;
  y = (aPos.y / 4) + y / 4;

  gl_Position = vec4(x, y, aPos.z, 1.0);
}
