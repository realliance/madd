#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "system.h"

#include "components/shadercomponent.h"
#include "components/component.h"
#include <vector>
#include <map>

struct Shader{
  unsigned int id;
  unsigned int shaderType;
  unsigned int program;
};

struct ProgramInfo{
  uint ID;
  uint shade;
  uint model;
  uint view;
  uint projection;
  uint time;
  uint textureEnabled;
};

class ShaderSystem : public System{
public:

  void Init();
  ~ShaderSystem();
  bool Register(Component* component);
  bool Unregister(Component* component);
  void Update();

  std::vector<ComponentType> Types() { return {ShaderComponent{}.Type()};}
  std::string Name() { return "ShaderSystem"; }
  std::vector<std::string> Requires() {return {"GlfwSystem"};};

  void Enable(ShaderComponent& s);
  unsigned int GetUniformLocation(ShaderComponent& s, std::string name);
  void SetMartix4fUniform(unsigned int location, glm::mat4* data);
  void SetFloat4fUniform(unsigned int location, glm::vec4* data);
  void SetFloatUniform(unsigned int location, float data);
  void SetIntUniform(unsigned int location, int data);
  void SetShade(ShaderComponent& s, glm::vec4* shade);
  void SetModel(ShaderComponent& s, glm::mat4* model);
  void SetView(ShaderComponent& s, glm::mat4* view);
  void SetProjection(ShaderComponent& s, glm::mat4* projection);
  void SetTime(ShaderComponent& s, double time);
  void SetTextureEnabled(ShaderComponent& s, bool enabled);
private:
  void initialize(ShaderComponent& s);
  uint constructShader(std::string shaderFileName);
  void destruct(ShaderComponent& s);
  std::vector<ShaderComponent*> shaders;
  std::map<ComponentID, ProgramInfo> program;
  ProgramInfo activeProgram;
};

