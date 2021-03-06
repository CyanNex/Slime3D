#include <collision/ColliderSet.h>

bool cColliderSet::Collides(cCollider* pCollider, const glm::mat4& tColliderMatrix)
{
    // The base distance is the size of the collider plus some padding
    uint uiBaseDist = pCollider->GetSize() + COLLIDER_PADDING;

    // Loop over all colliders in this set
    for (cCollider* pWorldCollider : papColliders)
    {
        // Make sure the collider doesn't collide with itself
        if (pWorldCollider != pCollider)
        {
            // The minimum distance in which we want to check is the size of this collider plus the base size
            uint uiMinDist = pWorldCollider->GetSize() + uiBaseDist;
            // Calculate the distance between the two colliders
            uint uiDist = (uint) glm::distance(pWorldCollider->ptWorldPosition, pCollider->ptWorldPosition);

            // If the distance is less than the minimum, check for collisions
            if (uiDist < uiMinDist)
            {
                if (pCollider->Collides(tColliderMatrix, pWorldCollider))
                {
                    return true;
                }
            }
        }
    }

    return false;
}
