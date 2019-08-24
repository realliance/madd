#ifndef MOUSEEVENTCOMPONENT_H
#define MOUSEEVENTCOMPONENT_H

#include "components/component.h"
#include <functional>
typedef std::function<void(Component*, double,double)> mouseCB;
struct MouseEventComponent : public Component{
  mouseCB callback;
  Component* c;
};

#endif // !MOUSEEVENTCOMPONENT_H

