#pragma once

#include <pch.h>

class cInvalidatable
{
private:
    bool pbInvalidated = true;

public:
    virtual bool Invalidated();
    virtual void Validate();
    virtual void Invalidate();
};
