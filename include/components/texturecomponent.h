#pragma once

#include "components/component.h"
#include <sys/types.h>
#include <string>
class TextureSystem;
struct TextureComponent : public Component{
  std::string filename;
  uint id;
  friend class TextureSystem;
  private:
    std::string _filename;
};

