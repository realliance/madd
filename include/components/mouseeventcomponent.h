#pragma once

#include "components/component.h"
#include "components/windowcomponent.h"
#include <functional>

typedef std::function<void(Component*, WindowComponent*, double,double)> mouseCB;
struct MouseEventComponent : public Component{
  mouseCB callback;
  Component* c;
  ComponentType Type(); 
  private: static ComponentType cType;
};


