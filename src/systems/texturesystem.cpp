#include <glad/glad.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "texturesystem.h"
#include "madd.h"

SystemType TextureSystem::sType = Madd::GetNewSystemType();

bool TextureSystem::Register(Component* component){
  loadTexture(*dynamic_cast<TextureComponent *>(component));
  return true;
}

bool TextureSystem::Unregister(Component* component){
  if(textureBuffer.contains(component->cID)){
    Destruct(component->cID);
    textureBuffer.erase(component->cID);
    return true;
  }
  return false;
}

void TextureSystem::loadTexture(TextureComponent& tex){
  glGenTextures(1, &textureBuffer[tex.cID]);
  glBindTexture(GL_TEXTURE_2D, textureBuffer[tex.cID]);
  // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load and generate the texture
  int width, height, nrChannels;
  unsigned char *data = stbi_load(("assets/"+tex.filename).c_str(), &width, &height, &nrChannels, 0);
  if (data){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
  }else{
    std::cout << "Failed to load texture" << std::endl;
    throw(tex);
  }
}

void TextureSystem::Destruct(ComponentID cID){
  glDeleteTextures(1, &textureBuffer[cID]);
}

void TextureSystem::Enable(TextureComponent* t){
  glBindTexture(GL_TEXTURE_2D, textureBuffer[t->cID]);
}
