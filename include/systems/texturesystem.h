#pragma once
#include <string>
#include <vector>
#include <map>
#include "components/texturecomponent.h"
#include "components/component.h"
#include "system.h"


class TextureSystem : public System{
  public:

    void Init();
    void Deinit();
    bool Register(Component* component);
    bool Unregister(Component* component);
    void Update();

    std::string Name() { return "TextureSystem"; }
    void Destruct(TextureComponent* t);
    void Enable(TextureComponent* t);
    void SetActiveTexture(int n);
  private:
    void loadTexture(TextureComponent& tex);
    std::vector<TextureComponent*> textures;
    std::map<ComponentID, uint> textureBuffer;
};

