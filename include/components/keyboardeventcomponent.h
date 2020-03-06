#pragma once

#include "components/component.h"
#include "components/windowcomponent.h"
#include <functional>

typedef std::function<void(Component*, WindowComponent*, int,int)> keyCB;
struct KeyboardEventComponent : public Component{
  keyCB callback;
  Component* c;
  uint code;
  uint mods;
  ComponentType Type(); 
  private: static ComponentType cType;
};


