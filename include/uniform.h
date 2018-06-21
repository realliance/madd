#ifndef UNIFORM_H
#define UNIFORM_H

#include <string>

class Uniform{
    public:
        Uniform();
        ~Uniform();
    private:
        std::string name;
        int location;
        bool dynamic;
        void* staticData;
        void* (*dynamicData)();
};

#endif //UNIFORM_H