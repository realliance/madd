#ifndef TEXTURE_H
#define TEXTURE_H
#include <string.h>
#include "texturecomponent.h"

class Texture{
    public:
        static TextureComponent Construct(std::string fileName);
        static void Deconstruct(TextureComponent t);
        static void Enable(TextureComponent t);
        static void SetActiveTexture(int n);
};

#endif //TEXTURE_H
