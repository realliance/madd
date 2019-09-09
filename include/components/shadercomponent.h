#pragma once

#include "components/component.h"
#include <sys/types.h>
#include <string>
class ShaderSystem;
struct ShaderComponent : public Component{
  std::string vertexShaderPath;
  std::string fragmentShaderPath;
  friend class ShaderSystem;
private:
  uint id;
};

