#include "assets/freecam.h"
#include <vector>
#include "eventhandler.h"
#include "madd.h"
FreeCam::FreeCam(Madd* context){
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    std::vector <unsigned int> keys = {KEY_W,KEY_A,KEY_S,KEY_D,KEY_LEFT_CONTROL,KEY_LEFT_SHIFT,KEY_F};
    context->GetEventHandler()->RegisterMultipleKeyCB(BIND(FreeCam::ProcessInput),keys);
    Camera::Init(context);
}

FreeCam::~FreeCam(){

}

void FreeCam::Update(){
    Camera::MovePosition(position);
    Camera::Update();
}

void FreeCam::ProcessInput(int key, int action){
    if(action != KEY_REPEAT){
        int x=position.x;
        int y=position.y;
        int z=position.z;
        float speed = 1.0f;
        if(action == KEY_RELEASE)
            speed = -speed;
        if(key==KEY_W)
            z -= speed;
        else if(key==KEY_A)
            x -= speed;
        else if(key==KEY_S)
            z += speed;
        else if(key==KEY_D)
            x += speed;
        else if(key==KEY_LEFT_SHIFT)
            y +=speed;
        else if(key==KEY_LEFT_CONTROL)
            y -=speed;
        else if(key==KEY_F && action == KEY_PRESS)
            Camera::SetPosition(glm::vec3(0.0f,0.0f,3.0f));
        position = glm::vec3(x,y,z);
    }
}