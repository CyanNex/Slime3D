#pragma once

#define COLLIDER_PADDING 2

#include <pch.h>
#include <collision/Collider.h>

class cColliderSet
{
public:
    std::vector<cCollider*> papColliders;

    bool Collides(cCollider* pCollider, const glm::mat4& tColliderMatrix);
};
