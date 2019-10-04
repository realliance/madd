#pragma once

#include "components/component.h"
#include <sys/types.h>
#include <string>
struct ShaderComponent : public Component{
  std::string vertexShaderPath;
  std::string fragmentShaderPath;
};

