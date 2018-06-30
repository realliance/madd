#include "game.h"
#include "gameobject.h"
#include "cube.h"

Game::Game(){
    const char *title = "test";
    Engine = new Madd(800, 600, title);
    GameObject* cube = new Cube(Engine);
    Engine->AddObject(cube);
}

Game::~Game(){
    delete Engine;
}

void Game::Run(){
    while(Engine->StayOpen()){
        Engine->Tick();
    }
}