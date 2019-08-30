#pragma once

#include "components/component.h"
#include <functional>
typedef std::function<void(Component*, double,double)> mouseCB;
struct MouseEventComponent : public Component{
  mouseCB callback;
  Component* c;
};


