#include "game.h"


Game::Game(){
    const char *title = "test";
    Engine = new Madd(800, 800, title);

    /*
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
    //*/
    /*
    std::vector<unsigned int> indices = {
        0, 1, 3, 3, 2, 0, //first face
        4, 5, 7, 7, 6, 4, //second face
        5, 1, 0, 0, 4, 5, //third face
        6, 2, 0, 0, 4, 6, //fourth face
        7, 3, 1, 1, 5, 7, //fifth face
        7, 3, 2, 2, 6, 7, //sixth face
    };
    //*/
    std::vector<float> vertices = {
        // positions       // colors
        0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	// top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,	// bottom right
       -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 	// bottom left
       -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f 	// top left 
    };

    std::vector<unsigned int> indices = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };  
    GameObject* rect = new GameObject(Engine);
    rect->RenderInit(vertices,indices,"default.vs","default.fs", true);
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