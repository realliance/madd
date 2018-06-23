#include "game.h"


Game::Game(){
    const char *title = "test";
    Engine = new Madd(800, 800, title);
    //*
    bool rgbcolor = true;
    std::vector<float> vertices = {
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.6f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.8f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.8f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.3f, 0.1f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.8f, 0.0f, 0.8f,
        -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.5f, 0.8f
    };//*/
    //*
    std::vector<unsigned int> indices = {
        0, 1, 3, 3, 2, 0, //first face
        4, 5, 7, 7, 6, 4, //second face
        5, 1, 0, 0, 4, 5, //third face
        6, 2, 0, 0, 4, 6, //fourth face
        7, 3, 1, 1, 5, 7, //fifth face
        7, 3, 2, 2, 6, 7, //sixth face
    };//*/
    /*
    bool rgbcolor = false;
    std::vector<float> vertices = {
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f
    };//*/
    GameObject* rect = new GameObject(Engine);
    rect->RenderInit(vertices,indices,"default.vs","default.fs", rgbcolor);
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