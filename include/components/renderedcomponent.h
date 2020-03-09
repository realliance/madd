#pragma once

#include "component.h"
#include "components/shadercomponent.h"
#include "components/texturecomponent.h"
#include "components/meshcomponent.h"

#include <string>
#include <glm/glm.hpp>
#include <vector>

struct RenderedComponent : public Component{
  RenderedComponent(MeshComponent* mesh,
  TextureComponent* texture, ShaderComponent* shader,
  glm::mat4 model, glm::vec4 shade):
  mesh(mesh), texture(texture),
  shader(shader), model(model), shade(shade){}


  RenderedComponent(): mesh(nullptr), texture(nullptr),
  shader(nullptr), model(glm::mat4(1.0f)), shade(glm::vec4(1.0f)){};

  MeshComponent* mesh;
  TextureComponent* texture;
  ShaderComponent* shader;
  glm::mat4 model;
  glm::vec4 shade;
  ComponentType Type(); 
  private: static ComponentType cType;
};


