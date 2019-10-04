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
  ShaderComponent* shader;
  glm::mat4 model;
  glm::vec4 shade;
};


