#pragma once
#include <vector>
#include "components/component.h"
#include "components/meshcomponent.h"
#include "system.h"
#include <string>
#include <map>

class MeshSystem: public System {
public:
  void Init();
  void Deinit();
  bool Register(Component* component);
  bool Unregister(Component* component);
  void Update();

  std::string Name() { return "MeshSystem"; }
  void Draw(MeshComponent& m);
private:
  void initialize(MeshComponent& m);
  void destruct(MeshComponent& m);
  std::vector<MeshComponent*> mesh;
  std::map<ComponentID,uint> VAO;
  std::map<ComponentID,uint[2]> VBO;
};

