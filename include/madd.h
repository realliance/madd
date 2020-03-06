#pragma once

#include <vector>
#include <chrono>
#include <unordered_map>
/** Type Definition for chrono clock shorthand */
using Clock = std::chrono::high_resolution_clock;
/** Type Definition for chrono time_point shorthand */
using Time = Clock::time_point;

#include "components/component.h"
#include "system.h"

struct WindowComponent;
class Madd {
public:
  void Init();
  static Madd& GetInstance();
  void Deinit();
  void Register(System* s);
  void Register(std::vector<System*> sys);
  bool RegisterComponent(Component* c);
  bool UnRegisterComponent(Component* c);
  void Unregister(System* s);
  bool InitSystems();
  System* GetSystem(std::string s);
  static ComponentID GetNewComponentID();
  static ComponentType GetNewComponentType();

  void Run();
  void Tick();
  bool StayOpen(){return !close;}
  void Close(){close = true;}
  double GetTime();
  float GetDeltaTime();
  Madd(const Madd&) = delete;
  Madd& operator=(const Madd&) = delete;
private:
  Madd() = default;
  std::unordered_map<std::string,System*> systems;
  std::unordered_map<ComponentType,System*> systemTypes;
  static ComponentID currID;
  static ComponentType currType;

  void UpdateDeltaTime();
  std::chrono::duration<float> dTime;
  bool close;
  float timeScale;
  Time lastFrame;
  size_t framecounter;
  size_t lastframecount;
  double lastFPS;
};

