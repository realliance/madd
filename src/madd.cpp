#include "madd.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <stack>
#include <algorithm>
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

void Madd::UnregisterComponent(Component* c){
  unregisterComponent(c);
}

bool Madd::registerComponent(Component* c){
  if(components.contains(c->cID)){
    components[c->cID].references++;
    return true;
  }
  c->cID = ++currentCID;
  int i;
  bool success = true;
  for(i=0; i < systemCTypes[c->Type()].size(); i++){
    if(!systemCTypes[c->Type()][i]->ptr->Register(c)){
      success = false;
      break;
    }
  }
  if(success){
    components[c->cID] = {.ptr = c, .references=1};
    return true;
  }
  success = true;
  for(i--; i >= 0; i--){
    if(!systemCTypes[c->Type()][i]->ptr->Unregister(c)){
      success = false;
      break;
    }
  }
  if(!success){
    throw "Component failed to register and during cleanup, component failed to unregister";
  }
  return false;
}

void Madd::unregisterComponent(Component* c){
  components[c->cID].references--;
  if(components[c->cID].references > 0){
    return;
  }
  for(int i=0; i < systemCTypes[c->Type()].size(); i++){
    if(!systemCTypes[c->Type()][i]->ptr->Unregister(c)){
      throw "Failed to unregister Component: " + std::to_string(c->cID);
    }
  }
  components.erase(c->cID);
  return;
}

void Madd::LoadSystem(System* s){
  if(systemNames.contains(s->Name())){
    throw "Two Systems share the same name.";
  }
  systems[s->Type()] = new SystemInfo{
    .ptr = s,
    .type = s->Type(),
    .name = s->Name(),
    .state = UNINITIALIZED
  };
  for(const ComponentType& cType: s->ComponentTypes()){
    systemCTypes[cType].push_back(systems[s->Type()]);
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
  bool success = true;
  int i;
  for(i = 0; i < entity.size(); i++){
    if(!registerComponent(entity[i])){
      success = false;
      break;
    }
  }
  if(success){
    return eid;
  }
  for(; i >= 0; i--){
    try{
      unregisterComponent(entity[i]);
    }catch(std::string s){
      throw "Error occured unregistering Component: " + std::to_string(entity[i]->cID)
       + " while creating new entity: " + std::to_string(eid);
    }
  }
  entities.erase(eid);
  return 0;
}

bool Madd::DeleteEntity(EntityID eid){
  if(!entities.contains(eid)){
    return false;
  }
  for(auto & component : entities[eid] ){
    try{
      unregisterComponent(component);
    }catch(std::string s){
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

ComponentType Madd::currentCType = 0;
SystemType Madd::currentSType = 0;

void Madd::updateDeltaTime(){
  dTime = Clock::now() - lastFrame;
  lastFrame = Clock::now();
}
