#ifndef TEXTURE_H
#define TEXTURE_H
#include <string.h>
class Texture{
    public:
        Texture(std::string fileName);
        ~Texture();
        unsigned int GetID(){return id;}
    private:
        unsigned int id;
};

#endif //TEXTURE_H