#pragma once
#include <string>
#include <set>
#include <map>
#include "components/texturecomponent.h"
#include "components/component.h"
#include "system.h"


class TextureSystem : public System{
  public:

    void Init();
    ~TextureSystem();
    bool Register(Component* component);
    bool Unregister(Component* component);
    void Update();

    std::string Name() { return "TextureSystem"; }
    std::vector<std::string> Requires() {return {"GlfwSystem"};};
    void Destruct(ComponentID cID);
    void Enable(TextureComponent* t);
    void SetActiveTexture(int n);
  private:
    void loadTexture(TextureComponent& tex);
    std::map<ComponentID, uint> textureBuffer;
};

