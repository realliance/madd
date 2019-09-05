#pragma once

#include "components/component.h"
#include "components/shadercomponent.h"
#include "components/texturecomponent.h"
#include "components/vertexarraycomponent.h"

#include <string>
#include <glm/glm.hpp>
#include <vector>

struct RenderedComponent : public Component{
  std::string vsPath;
  std::string fsPath;
  std::vector<float> verticies;
  VertexArrayComponent VAO;
  std::vector<TextureComponent> textures;
  size_t textureN;
  ShaderComponent shader;

  unsigned int shaderTimeLocation;
  unsigned int modelLoc;
  unsigned int shadeLoc;
  unsigned int viewLoc;
  unsigned int projectionLoc;
  unsigned int textureLoc;
  glm::mat4 model;
  glm::vec4 shade;

  bool shouldRender;
};


