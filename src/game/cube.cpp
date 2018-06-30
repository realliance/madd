#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "cube.h"
#include "madd.h"
#include "camera.h"
#include "eventhandler.h"
Cube::Cube(Madd* context):context(context){
    std::vector<float> vertices = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    cubeMesh = new RenderedObject(this);
    cubeMesh->RenderInit(vertices,"default.vs","default.fs","container.jpg");
    std::vector <unsigned int> keys = {KEY_W,KEY_A,KEY_S,KEY_D,KEY_LEFT_CONTROL,KEY_LEFT_SHIFT,KEY_F}; 
    context->GetEventHandler()->RegisterMultipleKeyCB(BIND(Cube::ProcessInput),keys);
}

Cube::~Cube(){
    delete cubeMesh;
}

bool Cube::Render(){
    return cubeMesh->Render();
}

bool Cube::ReloadShaders(){
    return cubeMesh->LoadShader();
}

bool Cube::Update(){
    glm::mat4 trans = cubeMesh->GetTransformation();
    cubeMesh->SetTransformation(glm::rotate(trans, glm::clamp(context->GetTime(), -1.f, 1.f)/100.f, glm::vec3(1.0, -1.0, 1.0)));
    return true;
}

void Cube::ProcessInput(int key, int action){
    if(action == KEY_PRESS || action == KEY_REPEAT){
        switch(key){
            case KEY_A:
                context->GetMainCamera()->MovePosition(0.01f,0.0f,0.0f);
                break;
            case KEY_W:
                context->GetMainCamera()->MovePosition(0.0f,0.0f,0.01f);
                break;
            case KEY_D:
                context->GetMainCamera()->MovePosition(-0.01f,0.0f,0.0f);
                break;
            case KEY_S:
                context->GetMainCamera()->MovePosition(0.0f,0.0f,-0.01f);
                break;
            case KEY_LEFT_SHIFT:
                context->GetMainCamera()->MovePosition(0.0f,0.01f,0.0f);
                break;
            case KEY_LEFT_CONTROL:
                context->GetMainCamera()->MovePosition(0.0f,-0.01f,0.0f);
                break;
            case KEY_F:
                context->GetMainCamera()->SetPosition(0.0f,0.0f,-3.0f);
                break;
        }
    }
}