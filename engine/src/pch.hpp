#pragma once

#include <cassert>
#include <array>
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <queue>
#include <map>
#include <initializer_list>
#include <set>
#include <tuple>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <algorithm>
#include <functional>
#include <cinttypes>
#include <limits>
#include <memory>
#include <sstream>
#include <codecvt>
#include <unistd.h>
#include <vulkan/util/EngineLog.hpp>

#include <system.hpp>

#ifndef FSLEEP
#define FSLEEP

void fSleep(const int iSleepMS)
{
#if defined(LINUX)
    usleep(iSleepMS * 1000); // usleep takes sleep time in us (1 millionth of a second)
#elif defined(WINDOWS)
    Sleep(iSleepMS);
#endif
}

#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#define GLFW_INCLUDE_VULKAN                 // We want to use GLFW with Vulkan
#define GLM_FORCE_RADIANS                   // Force GLM to use radians everywhere
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES  // Force GLM to use aligned types by default
#define GLM_FORCE_DEPTH_ZERO_TO_ONE         // Vulkan uses a depth range from 0 to 1, so we need GLM to do the same

#define STB_IMAGE_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION

#include "../vendor/stb_image.h"
#include "../vendor/font/stb_font_arial_50_usascii.inl"
#include "../vendor/tiny_obj_loader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef std::string string;
typedef unsigned int uint;
typedef long long int64;
typedef unsigned long long uint64;
typedef unsigned char byte;
typedef std::string string;
typedef unsigned short ushort;
typedef char* cstring;

std::vector<string> splitString(string sInput, const string& sDelimiter) noexcept
{
    std::vector<string> asResult;
    while (!sInput.empty())
    {
        size_t ulIndex = sInput.find(sDelimiter);
        if (ulIndex != string::npos)
        {
            asResult.emplace_back(sInput.substr(0, ulIndex));
            sInput = sInput.substr(ulIndex + sDelimiter.size());
            if (sInput.empty())
            {
                asResult.push_back(sInput);
            }
        }
        else
        {
            asResult.push_back(sInput);
            sInput.clear();
        }
    }
    return asResult;
}

template<typename Base, typename T>
inline bool instanceOf(const T* pPtr)
{
    return dynamic_cast<const Base*>(pPtr) != nullptr;
}
