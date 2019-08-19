#version 330 core
#define M_PI 3.1415926535897932384626433832795
out vec4 FragColor;
in vec2 TexCoord;

uniform int textureEnabled;
uniform sampler2D ourTexture;
uniform vec4 shade;
vec4 FragTexture;

void main() {
  if(textureEnabled == 1){
    FragColor = texture(ourTexture, TexCoord) * shade;
  }else{
    FragColor = shade;
  }
}
