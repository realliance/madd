#pragma once

#include "components/component.h"
#include <functional>
typedef std::function<void(Component*, int,int)> keyCB;
struct KeyboardEventComponent : public Component{
  keyCB callback;
  Component* c;
  uint code;
  uint mods;
};


