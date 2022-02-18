#include <scene/camera/FirstPersonFlyCamera.h>

void cFirstPersonFlyCamera::Forward()
{
    if (!lockMovement)
        cameraPos += cameraSpeed * cameraFront;
}

void cFirstPersonFlyCamera::BackWard()
{
    if (!lockMovement)
        cameraPos -= cameraSpeed * cameraFront;
}

void cFirstPersonFlyCamera::MoveLeft()
{
    if (!lockMovement)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void cFirstPersonFlyCamera::MoveRight()
{
    if (!lockMovement)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void cFirstPersonFlyCamera::MoveUp()
{
    if (!lockMovement)
        cameraHeight += cameraSpeed;
//            cameraPos += cameraSpeed * cameraUp;
}

void cFirstPersonFlyCamera::MoveDown()
{
    if (!lockMovement)
        cameraHeight -= cameraSpeed;
//            cameraPos -= cameraSpeed * cameraUp;
}

void cFirstPersonFlyCamera::MovePivotX(float fMultiplier)
{

}

void cFirstPersonFlyCamera::MovePivotY(float fMultiplier)
{

}

void cFirstPersonFlyCamera::LookUp()
{
    pitch += cameraSpeedLook;
}

void cFirstPersonFlyCamera::LookDown()
{
    pitch -= cameraSpeedLook;
}

void cFirstPersonFlyCamera::LookLeft()
{
    yaw -= cameraSpeedLook;
}

void cFirstPersonFlyCamera::LookRight()
{
    yaw += cameraSpeedLook;
}

// is the end op the passthrough from the mouse input.
void cFirstPersonFlyCamera::LookMouseDiff(double dDeltaX, double dDeltaY)
{
    yaw += mouseSpeed * dDeltaX;
    pitch -= mouseSpeed * dDeltaY;
    // no flipping to the other side
    if (pitch < -80)
        pitch = -80;
    if (pitch > 80)
        pitch = 80;
}

void cFirstPersonFlyCamera::LookMouseWheelDiff(float x, float y)
{

}

// process the commits to the pv.
void cFirstPersonFlyCamera::ProcessUpdates()
{
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

    cameraPos.y = cameraHeight;
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

glm::mat4& cFirstPersonFlyCamera::GetViewMatrix()
{
    return this->view;
}

glm::vec3 cFirstPersonFlyCamera::GetPosition()
{
    return this->cameraPos;
}

void cFirstPersonFlyCamera::SetPosition(glm::vec3& position)
{
    this->cameraPos = position;
}

glm::vec3 cFirstPersonFlyCamera::GetFront()
{
    return this->cameraFront;
}

void cFirstPersonFlyCamera::SetFront(glm::vec3& front)
{
    this->cameraFront = front;
}

float cFirstPersonFlyCamera::GetPitch()
{
    return this->pitch;
}

void cFirstPersonFlyCamera::SetPitch(float pitch)
{
    this->pitch = pitch;
}

float cFirstPersonFlyCamera::GetYaw()
{
    return this->yaw;
}

void cFirstPersonFlyCamera::SetYaw(float yaw)
{
    this->yaw = yaw;
}