#pragma once
#include <string.h>
#include "texturecomponent.h"

class Texture{
    public:
        Texture() = delete;
        static TextureComponent Construct(std::string fileName);
        static void Destruct(TextureComponent t);
        static void Enable(TextureComponent t);
        static void SetActiveTexture(int n);
};

