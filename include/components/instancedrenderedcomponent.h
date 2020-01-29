#pragma once

#include "components/component.h"
#include "components/shadercomponent.h"
#include "components/texturecomponent.h"
#include "components/meshcomponent.h"

#include <string>
#include <glm/glm.hpp>
#include <vector>

struct InstancedRenderedComponent : public Component{
  InstancedRenderedComponent(MeshComponent* mesh,
  TextureComponent* texture, ShaderComponent* shader):
  mesh(mesh), texture(texture), shader(shader){}
  
  InstancedRenderedComponent(): mesh(nullptr), texture(nullptr),
  shader(nullptr), instancedshade(false),positiononlymodels(false){}

  bool instancedshade;
  bool positiononlymodels;

  MeshComponent* mesh;
  TextureComponent* texture;
  ShaderComponent* shader;
  glm::vec4 shade;
  std::vector<glm::mat4> models;
  std::vector<glm::vec3> posmodels;
  std::vector<glm::vec4> shades;
};


