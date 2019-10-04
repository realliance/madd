#pragma once

#include "components/component.h"
#include <sys/types.h>
#include <string>
class TextureSystem;
struct TextureComponent : public Component{
  std::string filename;
};

