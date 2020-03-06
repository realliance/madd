#pragma once
#include <string>
#include <set>
#include <map>
#include "components/texturecomponent.h"
#include "components/component.h"
#include "system.h"


class TextureSystem : public System{
  public:

    void Init(){}
    void Deinit(){}
    bool Register(Component* component);
    bool Unregister(Component* component);
    void Update(){}

    std::vector<ComponentType> ComponentTypes() { return {TextureComponent{}.Type()};}
    std::string Name() { return "TextureSystem"; }
    SystemType Type() { return sType; }
    std::vector<std::string> Requires() {return {"GlfwSystem"};};
    void Destruct(ComponentID cID);
    void Enable(TextureComponent* t);
    void SetActiveTexture(int n);
  private:
    void loadTexture(TextureComponent& tex);
    std::map<ComponentID, uint> textureBuffer;
    static SystemType sType;
};

