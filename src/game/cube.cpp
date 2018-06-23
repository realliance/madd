#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "cube.h"
#include "madd.h"
Cube::Cube(Madd* context):context(context){
    std::vector<float> vertices = {
         0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,	1.0f, 0.6f, 0.0f,	1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,	1.0f, 0.8f, 0.0f,	0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,	0.8f, 1.0f, 0.0f,	1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,	0.3f, 0.1f, 1.0f,	1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	0.8f, 0.0f, 0.8f,	0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,	0.0f, 0.5f, 0.8f,	0.0f, 1.0f
    };
    std::vector<unsigned int> indices = {
        0, 1, 3, 3, 2, 0, //first face
        4, 5, 7, 7, 6, 4, //second face
        5, 1, 0, 0, 4, 5, //third face
        6, 2, 0, 0, 4, 6, //fourth face
        7, 3, 1, 1, 5, 7, //fifth face
        7, 3, 2, 2, 6, 7, //sixth face
    };
    cubeMesh = new RenderedObject(this);
    cubeMesh->RenderInit(vertices,indices,"default.vs","default.fs","container.jpg");
}

Cube::~Cube(){
    delete cubeMesh;
}

bool Cube::Render(){
    return cubeMesh->Render();
}

bool Cube::ReloadShaders(){
    return cubeMesh->ReloadShader();
}

bool Cube::Update(){
    glm::mat4 trans = cubeMesh->GetTransformation();
    cubeMesh->SetTransformation(glm::rotate(trans, glm::clamp(context->GetTime(), -1.f, 1.f)/100.f, glm::vec3(1.0, -1.0, 1.0)));
    return true;
}