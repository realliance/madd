#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <components/cameracomponent.h>

class Camera{
  public:
    static CameraComponent Construct();
    static void Destruct(CameraComponent& c);
    static void UpdateProjection(CameraComponent& c);
    static void LookAt(CameraComponent& c, glm::vec3 pos);
    static void SetPosition(CameraComponent& c,glm::vec3 pos);
    static void SetPitchAndYaw(CameraComponent& c, float pitch, float yaw);
    static void MovePosition(CameraComponent& c, glm::vec3 movementVector);
};

#endif //CAMERA_H
