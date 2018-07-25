#ifndef TEXTURE_H
#define TEXTURE_H
#include <string.h>
class Texture{
    public:
        Texture(std::string fileName);
        ~Texture();
        unsigned int GetID(){return id;}
        void Enable();
        static void SetActiveTexture(int n);
    private:
        unsigned int id;
};

#endif //TEXTURE_H