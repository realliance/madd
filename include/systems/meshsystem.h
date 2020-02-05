#pragma once
#include <vector>
#include "components/component.h"
#include "components/meshcomponent.h"
#include "systems/glfwsystem.h"
#include "system.h"
#include <string>
#include <map>

class MeshSystem: public System {
public:
  void Init();
  ~MeshSystem();
  bool Register(Component* component);
  bool Unregister(Component* component);
  void Update();
  uint CreateVAO(Component* component);
  std::string Name() { return "MeshSystem"; }
  std::vector<std::string> Requires() {return {"GlfwSystem"};};
  void Draw(MeshComponent& m);
private:
  struct MeshData {
    uint VBO[2];
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texcoords;
    MeshComponent* mesh;
  };
  void initialize(MeshData& m);
  void destruct(MeshData& m);
  std::map<ComponentID,MeshData> meshdata;
  GlfwSystem* glfw;
};

