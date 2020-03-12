#include "madd.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <stack>
#include <set>

void Madd::Init() {
  framecounter = 0;
  lastframecount = 0;
  close = false;
  timeScale = 1.0f;
  lastFPS = glfwGetTime();
  lastFrame = Clock::now();
  currentEID = 0;
  currentCID = 0;
  currentCType = 0;
  currentSType = 0;
}

void Madd::Deinit() {
  for(auto const& [name, sys] : systems){
    sys->state = UNINITIALIZED;
    sys->ptr->Deinit();
  }
  for(auto const& [name, sysinfo] : systems){
    delete sysinfo->ptr;
    delete systems[sysinfo->type];
  }
  systems.clear();
}

Madd& Madd::GetInstance() {
  static Madd instance;
  return instance;
}

bool Madd::RegisterComponent(Component* c){
  return registerComponent(c);
}

bool Madd::UnregisterComponent(Component* c){
  return unregisterComponent(c);
}

bool Madd::registerComponent(Component* c){
  return systemCTypes[c->Type()]->ptr->Register(c);
}

bool Madd::unregisterComponent(Component* c){
  return systemCTypes[c->Type()]->ptr->Unregister(c);
}

void Madd::LoadSystem(System* s){
  if(systemNames.contains(s->Name())){
    throw "Two Systems share the same name.";
  }
  for(const ComponentType& cType: s->ComponentTypes()){
    if(systemCTypes.contains(cType)){
      throw "Type claimed by two systems.";
    }
  }
  systems[s->Type()] = new SystemInfo{
    .ptr = s,
    .type = s->Type(),
    .name = s->Name(),
    .state = UNINITIALIZED
  };
  for(const ComponentType& cType: s->ComponentTypes()){
    systemCTypes[cType] = systems[s->Type()];
  }
  systemNames[s->Name()] = s->Type();
}

void Madd::LoadSystems(std::vector<System*> sys){
  for(System* s : sys){
    LoadSystem(s);
  }
}

void Madd::UnLoadSystem(System* s){
  throw "Not implemented";
}

void Madd::InitSystems(){
  for(auto& [sType, sysInfo] : systems){
    initSystem(sysInfo);
  }
}

void Madd::initSystem(SystemInfo* sysInfo){
  if(sysInfo->state == INITIALIZED){
    return;
  }
  for(const auto& require: sysInfo->ptr->Requires()){
    if(systemNames.contains(require)){
      initSystem(systems[systemNames[require]]);
    }else{
      throw require + " is required by " + sysInfo->name + " but not included.";
    }
  }
  sysInfo->ptr->Init();
  sysInfo->state = INITIALIZED;
}

ComponentID Madd::GetNewComponentID(){
  return ++currentCID;
}
ComponentType Madd::GetNewComponentType(){
  return ++currentCType;
}
SystemType Madd::GetNewSystemType(){
  return ++currentSType;
}

void Madd::Run(){
  while(stayOpen()){
    tick();
    if(framecounter % 60 == 0){
      std::cout << (framecounter-lastframecount)/(GetTime()-lastFPS) << '\r' << std::flush;
      lastframecount = framecounter;
      lastFPS = GetTime();
    }
    framecounter++;
  }
}

void Madd::Close(){
  close = true;
}

double Madd::GetTime(){
  return glfwGetTime();
}

float Madd::GetDeltaTime(){
  return dTime.count() * timeScale;
}

EntityID Madd::CreateEntity(Entity entity){
  EntityID eid = ++currentEID;
  entities[eid] = entity;
  for(auto & component : entity ){
    if(!registerComponent(component)){
      return 0;
    }
  }
  return eid;
}

bool Madd::DeleteEntity(EntityID eid){
  if(!entities.contains(eid)){
    return false;
  }
  for(auto & component : entities[eid] ){
    if(!unregisterComponent(component)){
      throw "Error occured unregistering Component: " + std::to_string(component->cID)
       + " while deleting entity: " + std::to_string(eid);
    }
  }
  entities.erase(eid);
  return true;
}

bool Madd::stayOpen(){
  return !close;
}

void Madd::tick(){
  for(auto const& [name, sys] : systems){
      sys->ptr->Update();
  }
  updateDeltaTime();
}

System* Madd::getSystem(SystemType sType){
  if(systems.contains(sType)){
    return systems[sType]->ptr;
  }
  return nullptr;
}

ComponentID Madd::currentCID = 0;
ComponentType Madd::currentCType = 0;
SystemType Madd::currentSType = 0;

void Madd::updateDeltaTime(){
  dTime = Clock::now() - lastFrame;
  lastFrame = Clock::now();
}
