#include <glad/glad.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "texturesystem.h"
#include "madd.h"

void TextureSystem::Init(){}

void TextureSystem::Deinit(){
    delete this;
}

bool TextureSystem::Register(Component* component){
  component->cID = Madd::GetInstance().GetNewComponentID();
  loadTexture(*dynamic_cast<TextureComponent *>(component));
  textures.push_back(dynamic_cast<TextureComponent *>(component));
  return true;
}

bool TextureSystem::Unregister(Component* component){
  for (auto i = begin(textures); i != end(textures); i++) {
    if ((*i)->cID == component->cID) {
      Destruct(*i);
      textures.erase(i);
      return true;
    }
  }
  return false;
}

void TextureSystem::Update(){
}

void TextureSystem::loadTexture(TextureComponent& tex){
    glGenTextures(1, &tex.id);
    glBindTexture(GL_TEXTURE_2D, tex.id);
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

void TextureSystem::Destruct(TextureComponent* t){
    glDeleteTextures(1, &t->id);
}

void TextureSystem::Enable(TextureComponent* t){
    glBindTexture(GL_TEXTURE_2D, t->id);
}
