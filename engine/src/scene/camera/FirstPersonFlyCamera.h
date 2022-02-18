#pragma once

#include <scene/camera/Camera.h>

class cFirstPersonFlyCamera : public cCamera
{
    void Forward() override;
    void BackWard() override;
    void MoveLeft() override;
    void MoveRight() override;
    void MoveUp() override;
    void MoveDown() override;
    void MovePivotX(float fMultiplier) override;
    void MovePivotY(float fMultiplier) override;
    void LookUp() override;
    void LookDown() override;
    void LookLeft() override;
    void LookRight() override;
    void LookMouseDiff(double dDeltaX, double dDeltaY) override;
    void LookMouseWheelDiff(float x, float y) override;
    void ProcessUpdates() override;
    glm::mat4& GetViewMatrix() override;
    glm::vec3 GetPosition() override;
    void SetPosition(glm::vec3& position) override;
    glm::vec3 GetFront() override;
    void SetFront(glm::vec3& front) override;
    float GetPitch() override;
    void SetPitch(float pitch) override;
    float GetYaw() override;
    void SetYaw(float yaw) override;
};
