#pragma once

#include <vector>
#include "components/component.h"
#include <sys/types.h>
class MeshSystem;
struct MeshComponent : public Component{
  std::vector<float> vertices;
  friend class MeshSystem;
private:
  uint VAO;
  uint VBO;
};


