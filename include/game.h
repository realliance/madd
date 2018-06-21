#ifndef GAME_H
#define GAME_H
#include "madd.h"

class Game{
    public:
        Game();
        ~Game();
        void Run();
    private:
        Madd* Engine;
};

#endif //GAME_H