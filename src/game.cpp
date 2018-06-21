#include "game.h"


Game::Game(){
    const char *title = "test";
    Engine = new Madd(800, 800, title);

    std::vector<float> vertices = {
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
    };

    std::vector<unsigned int> indices = {
        0, 1, 3, 3, 2, 0, //first face
        4, 5, 7, 7, 6, 4, //second face
        5, 1, 0, 0, 4, 5, //third face
        6, 2, 0, 0, 4, 6, //fourth face
        7, 3, 1, 1, 5, 7, //fifth face
        7, 3, 2, 2, 6, 7, //sixth face
    };

    GameObject* rect = new GameObject();
    rect->RenderInit(vertices,indices,"default.vs","default.fs");
    Engine->addObject(rect);
}

Game::~Game(){
    delete Engine;
}

void Game::Run(){
    while(Engine->stayOpen()){
        Engine->Tick();
    }
}