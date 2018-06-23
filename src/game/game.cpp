#include "game.h"
#include "gameobject.h"
#include "cube.h"

Game::Game(){
    const char *title = "test";
    Engine = new Madd(800, 800, title);
    GameObject* cube = new Cube(Engine);
    Engine->addObject(cube);
}

Game::~Game(){
    delete Engine;
}

void Game::Run(){
    while(Engine->stayOpen()){
        Engine->Tick();
    }
}