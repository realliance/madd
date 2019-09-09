#pragma once

#include <string>
#include <vector>

#include "system.h"
#include "component_template.h"


class TemplateSystem : public System {
  void Init();
  void Deinit();;
  bool Register(Component* component);
  bool Unregister(Component* component);
  void Update();
  std::string Name() { return "TemplateSystem"; }
private:
  std::vector<TemplateComponent*> objects;
};