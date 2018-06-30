#version 330 core
#define M_PI 3.1415926535897932384626433832795
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main() {
  FragColor = texture(ourTexture, TexCoord);
}
