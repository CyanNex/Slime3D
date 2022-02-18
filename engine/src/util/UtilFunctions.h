#pragma once

#include <pch.h>

void sleep_ms(uint uiSleepDurationMs);

template<typename Base, typename T>
inline bool instanceOf(const T* pPtr)
{
    return dynamic_cast<const Base*>(pPtr) != nullptr;
}
