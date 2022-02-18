#pragma once

#include <pch.h>

class iInputHandler
{
public:
    virtual void HandleMouse(double dDeltaX, double dDeltaY);
    virtual void HandleKey(uint uiKeyCode, uint uiAction);
    virtual void HandleScroll(double dOffsetX, double dOffsetY);
    virtual void HandleCharacter(char cCharacter);
    virtual void HandleMouseButton(uint uiButton, double dXPos, double dYPos, int iAction);
};

