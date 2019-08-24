#ifndef KEYBOARDEVENTCOMPONENT_H
#define KEYBOARDEVENTCOMPONENT_H

#include "components/component.h"
#include <functional>
typedef std::function<void(Component*, int,int)> keyCB;
struct KeyboardEventComponent : public Component{
  keyCB callback;
  Component* c;
  uint code;
  uint mods;
};

#endif // !KEYBOARDEVENTCOMPONENT_H

