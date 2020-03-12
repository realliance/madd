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
#include "entity.h"

struct WindowComponent;

struct SystemInfo{
  System* ptr;
  SystemType type;
  std::string name;
  SystemState state;
};

class Madd {
public:
  //Singleton (May remove?)
  Madd(const Madd&) = delete;
  Madd& operator=(const Madd&) = delete;
  void Init();
  void Deinit();
  static Madd& GetInstance();

  //Component creation and deletion (Deprecated)
  bool RegisterComponent(Component* c);
  bool UnregisterComponent(Component* c);

  //System creation and deletion
  void LoadSystem(System* s);
  void LoadSystems(std::vector<System*> sys);
  void UnLoadSystem(System* s);
  void InitSystems();

  //System Information
  template <class S>
  S* GetSystem();
  template <class S>
  SystemState IsInit();

  //Entity and Type Functions
  static ComponentID GetNewComponentID();
  static ComponentType GetNewComponentType();
  static SystemType GetNewSystemType();

  //Execution
  void Run();
  void Close();

  //Time
  double GetTime();
  float GetDeltaTime();

  //Entities
  EntityID CreateEntity(Entity* entity);
  bool DeleteEntity(EntityID);

private:
  //Singleton (May remove?)
  Madd() = default;

  //Destruction
  void destruct(System*);

  //Execution
  bool stayOpen();
  void tick();

  //SystemInit
  void initSystem(SystemInfo* sysInfo);

  //Entity and System Storage
  std::unordered_map<SystemType,SystemInfo*> systems;


  //System Info (might convert to a struct if more information is needed)
  System* getSystem(SystemType sType);
  std::unordered_map<ComponentType,SystemInfo*> systemCTypes;
  std::unordered_map<std::string,SystemType> systemNames;

  //Entity and Type counters
  static ComponentID currentCID;
  static EntityID currentEID;
  static ComponentType currentCType;
  static SystemType currentSType;

  //Time and FPS
  void updateDeltaTime();
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
  return dynamic_cast<S*>(getSystem(S{}.Type()));
}

template <class S>
SystemState Madd::IsInit(){
  SystemType sType = S{}.Type();
  if(systems.contains(sType)){
    return systems[sType]->state;
  }
  return SystemState::NONEXISTENT;
}