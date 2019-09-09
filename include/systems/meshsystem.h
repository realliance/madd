#pragma once
#include <vector>
#include "components/meshcomponent.h"
#include "system.h"
#include <string>
class MeshSystem: public System {
public:
  void Init();
  void Deinit();
  bool Register(Component* component);
  bool Unregister(Component* component);
  void Update();

  std::string Name() { return "MeshSystem"; }
  static void Draw(MeshComponent& m);
private:
  void initialize(MeshComponent& m);
  void destruct(MeshComponent& m);
  std::vector<MeshComponent*> mesh;
};

