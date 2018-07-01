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
    float speed = 1.0f;
    
        
    if(action == KEY_PRESS){
        switch(key){
            case KEY_A:
                x+=speed;
                break;
            case KEY_W:
                z+=speed;
                break;
            case KEY_D:
                x-=speed;
                break;
            case KEY_S:
                z-=speed;
                break;
            case KEY_LEFT_SHIFT:
                y-=speed;
                break;
            case KEY_LEFT_CONTROL:
                y+=speed;
                break;
            case KEY_F:
                context->GetMainCamera()->SetPosition(0.0f,0.0f,-3.0f);
                break;
        }
    }else if(action == KEY_RELEASE){
        switch(key){
            case KEY_A:
                x=0;
                break;
            case KEY_W:
                z=0;
                break;
            case KEY_D:
                x=0;
                break;
            case KEY_S:
                z=0;
                break;
            case KEY_LEFT_SHIFT:
                y=0;
                break;
            case KEY_LEFT_CONTROL:
                y=0;
                break;
        }
    }
    context->GetMainCamera()->MovePosition(x,y,z);
}