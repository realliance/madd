#include "system_template.h"
#include "madd.h"

void TemplateSystem::Init() {

}

void TemplateSystem::Deinit(){

}

bool TemplateSystem::Register(Component* component){
  component->cID = Madd::GetInstance().GetNewComponentID();
  objects.push_back(dynamic_cast<TemplateComponent*>(component));
  return true;
}



bool TemplateSystem::Unregister(Component* component){
  for(auto i = begin(objects); i != end(objects); i++){
    if((*i)->cID == component->cID){
      objects.erase(i);
      return true;
    }
  }
  return false;
}

void TemplateSystem::Update(){
  for (TemplateSystem *t : objects) {

  }
}