#pragma once

#include <vector>
#include <chrono>
#include <unordered_map>
/** Type Definition for chrono clock shorthand */
using Clock = std::chrono::high_resolution_clock;
/** Type Definition for chrono time_point shorthand */
using Time = Clock::time_point;

#include "component.h"
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
  bool UnregisterComponent(Component* c);
  void Unregister(System* s);
  bool InitSystems();
  System* GetSystem(std::string s);
  template <class S>
  S* GetSystem();
  template <class S>
  SystemState IsInit();
  static ComponentID GetNewComponentID();
  static ComponentType GetNewComponentType();
  static SystemType GetNewSystemType();

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
  std::unordered_map<ComponentType,System*> systemCTypes;
  std::unordered_map<SystemType,System*> systemSTypes;
  std::unordered_map<SystemType,SystemState> systemStates;
  static ComponentID currentCID;
  static ComponentType currentCType;
  static SystemType currentSType;

  void UpdateDeltaTime();
  void destruct(System*);
  std::chrono::duration<float> dTime;
  bool close;
  float timeScale;
  Time lastFrame;
  size_t framecounter;
  size_t lastframecount;
  double lastFPS;
};

template <class S>
S* Madd::GetSystem(){  
  SystemType sType = S{}.Type();
  if(systemSTypes.contains(sType)){
    return dynamic_cast<S*>(systemSTypes[S{}.Type()]);
  }
  return nullptr;
}

template <class S>
SystemState Madd::IsInit(){
  SystemType sType = S{}.Type();
  if(systemSTypes.contains(sType)){
    return systemStates[sType];
  }
  return SystemState::NONEXISTENT;
}