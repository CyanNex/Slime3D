#pragma once

#include <pch.h>

class iTickTask
{
public:
    virtual ~iTickTask() = default;
    virtual void Tick() = 0;
};
