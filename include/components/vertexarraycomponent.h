#pragma once

#include "components/component.h"
#include <sys/types.h>

struct VertexArrayComponent : public Component{
  uint VAO;
  uint VBO;
  int verticesSize;
};


