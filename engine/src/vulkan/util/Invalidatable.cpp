#include <vulkan/util/Invalidatable.h>

bool cInvalidatable::Invalidated()
{
    return pbInvalidated;
}

void cInvalidatable::Validate()
{
    pbInvalidated = false;
}

void cInvalidatable::Invalidate()
{
    pbInvalidated = true;
}
