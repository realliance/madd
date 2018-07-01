#include <glm/gtc/matrix_transform.hpp>
#include "gamecamera.h"
#include "madd.h"
#include "assets/freecam.h"
#include "eventhandler.h"
GameCamera::GameCamera(Madd* context):context(context){
    cameraObj = new FreeCam(context);
    context->SetMainCamera(cameraObj); 
}

GameCamera::~GameCamera(){
   delete cameraObj;
   context->SetMainCamera(NULL);
}

bool GameCamera::Update(){
    cameraObj->Update();
    return true;
}

bool GameCamera::ReloadShaders(){return true;}
bool GameCamera::Render(){return true;}