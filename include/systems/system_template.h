#pragma once

#include <string>
#include <vector>

#include "system.h"
#include "component_template.h"


class TemplateSystem : public System {
  void Init();
  ~TemplateSystem();
  bool Register(Component* component);
  bool Unregister(Component* component);
  void Update();
  std::string Name() { return "TemplateSystem"; }
  std::vector<std::string> Requires() {return {};};
private:
  std::vector<TemplateComponent*> objects;
};