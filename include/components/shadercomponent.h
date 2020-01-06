#pragma once

#include "components/component.h"
#include <sys/types.h>
#include <string>
#include <vector>
struct ShaderComponent : public Component{
  std::string vertexShaderPath;
  std::string fragmentShaderPath;
  std::vector<std::string> uniformNames;
};

