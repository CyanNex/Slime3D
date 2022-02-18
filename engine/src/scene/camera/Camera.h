#pragma once

#include <pch.h>
#include <scene/object/BaseObject.h>

class cCamera
{
public:
    float fFoV = 45.0f;
    float fZNear = 0.1f;
    float fZFar = 800.0f;

    glm::vec3 cameraPos = glm::vec3(2.0f, 7.0f, 2.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 direction;

    float yaw = 0;
    float pitch = 0;

    const float cameraSpeed = 0.05f;
    const float cameraSpeedLook = 1.0f;
    float mouseSpeed = 0.07f;

    glm::mat4 view = glm::mat4(1.0f);
public:
    virtual ~cCamera() = default;

    float cameraHeight = 1.75f;

    bool lockHeight = true;
    bool lockMovement = false;

    // bus camera
    const float cameraScrollSpeed = 0.5f;
    float orbitDistance = 30.0f;
    cBaseObject* cameraPivotObject;
    glm::vec3 cameraPivotPos;
    glm::vec3 cameraPivotChanges;

    virtual void Reset();

    virtual void Forward() = 0;
    virtual void BackWard() = 0;
    virtual void MoveLeft() = 0;
    virtual void MoveRight() = 0;
    virtual void MoveUp() = 0;
    virtual void MoveDown() = 0;
    virtual void MovePivotX(float fMultiplier) = 0;
    virtual void MovePivotY(float fMultiplier) = 0;
    virtual void LookUp() = 0;
    virtual void LookDown() = 0;
    virtual void LookLeft() = 0;
    virtual void LookRight() = 0;
    // is the end op the passthrough from the mouse input.
    virtual void LookMouseDiff(double dDeltaX, double dDeltaY) = 0;
    // process the commits to the pv.
    virtual void LookMouseWheelDiff(float x, float y) = 0;
    virtual void ProcessUpdates() = 0;
    // sets the pv and position on the passed shader.
    virtual glm::mat4& GetViewMatrix() = 0;
    virtual glm::vec3 GetPosition() = 0;
    virtual void SetPosition(glm::vec3& position) = 0;
    virtual glm::vec3 GetFront() = 0;
    virtual void SetFront(glm::vec3& front) = 0;
    virtual float GetPitch() = 0;
    virtual void SetPitch(float pitch) = 0;
    virtual float GetYaw() = 0;
    virtual void SetYaw(float yaw) = 0;
};
