#pragma once

#include "components/component.h"
#include "components/shadercomponent.h"
#include "components/texturecomponent.h"
#include "components/meshcomponent.h"

#include <string>
#include <glm/glm.hpp>
#include <vector>

struct RenderedComponent : public Component{
  MeshComponent* mesh;
  TextureComponent* texture;
  size_t textureN;
  ShaderComponent* shader;

  // unsigned int shaderTimeLocation;
  // unsigned int modelLoc;
  // unsigned int shadeLoc;
  // unsigned int viewLoc;
  // unsigned int projectionLoc;
  // unsigned int textureLoc;
  glm::mat4 model;
  glm::vec4 shade;
};


