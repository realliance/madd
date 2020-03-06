#pragma once

#include "components/component.h"
#include <sys/types.h>
#include <string>

struct TextureComponent : public Component{
  std::string filename;
  ComponentType Type(); 
  private: static ComponentType cType;
};

