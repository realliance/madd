#include "game.h"

Game::Game(){
    const char *title = "test";
    Engine = new Madd(800, 800, title);

    std::vector<float> vertices = {
        0.5f,  0.5f,  0.0f, // top right
        0.5f,  -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f  // top left
    };

    std::vector<unsigned int> indices = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    GameObject* rect = new GameObject();
    rect->RenderInit(vertices,indices,"default.vs","default.fs");
    Engine->addObject(rect);
    while(Engine->stayOpen()){
        Engine->Tick();
    }
}