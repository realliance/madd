#include <glad/glad.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "texture.h"

Texture::Texture(std::string fileName){
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load(("assets/"+fileName).c_str(), &width, &height, &nrChannels, 0);
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }else{
        std::cout << "Failed to load texture" << std::endl;
    }
}

Texture::~Texture(){
    glDeleteTextures(1, &id);
}

void Texture::Enable(){
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::SetActiveTexture(int n){
    glActiveTexture(GL_TEXTURE0+n);
}
