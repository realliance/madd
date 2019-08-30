#pragma once

#include "components/component.h"
#include <string>

class System{
  public:
    virtual void Init() = 0;
    virtual void Deinit() = 0;
    virtual bool Register(Component* component) = 0;
    virtual bool Unregister(Component* component) = 0;
    virtual void Update() = 0;
    virtual std::string Name() = 0;
};

