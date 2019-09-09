#pragma once
#include <string>
#include <vector>
#include "components/texturecomponent.h"
#include "system.h"


class TextureSystem : public System{
  public:

    void Init();
    void Deinit();
    bool Register(Component* component);
    bool Unregister(Component* component);
    void Update();

    std::string Name() { return "TextureSystem"; }
    static TextureComponent Construct(std::string fileName);
    static void Destruct(TextureComponent* t);
    static void Enable(TextureComponent* t);
    static void SetActiveTexture(int n);
  private:
    void loadTexture(TextureComponent& tex);
    std::vector<TextureComponent*> textures;
};

