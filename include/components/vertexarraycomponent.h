#ifndef VERTEXARRAYCOMPONENT_H
#define VERTEXARRAYCOMPONENT_H

#include "components/component.h"
#include <sys/types.h>

struct VertexArrayComponent : public Component{
  uint VAO;
  uint VBO;
  int verticesSize;
};

#endif // !VERTEXARRAYCOMPONENT_H

