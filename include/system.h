#pragma once

#include "component.h"
#include <string>
#include <vector>

typedef u_int32_t SystemType;

class System{
  public:
    virtual void Init() = 0;
    virtual void Deinit() = 0;
    virtual ~System() = default;
    virtual bool Register(Component* component) = 0;
    virtual bool Unregister(Component* component) = 0;
    virtual void Update() = 0;
    virtual std::string Name() = 0;
    virtual std::vector<std::string> Requires() = 0;
    virtual std::vector<ComponentType> ComponentTypes() = 0;
    virtual SystemType Type() = 0;
};

