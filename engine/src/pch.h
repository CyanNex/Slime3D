#pragma once

#include <system.h>

#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <cassert>
#include <set>
#include <stdexcept>
#include <fstream>

using namespace std::chrono;

#include <util/EngineLog.h>

#include <../vendor/stb_image.h>
#include <../vendor/font/stb_font_arial_50_usascii.inl>
#include <../vendor/tiny_obj_loader.h>

#define GLM_FORCE_RADIANS                   // Force GLM to use radians everywhere
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES  // Force GLM to use aligned types by default
#define GLM_FORCE_DEPTH_ZERO_TO_ONE         // Vulkan uses a depth range from 0 to 1, so we need GLM to do the same

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef std::string string;
typedef unsigned int uint;
typedef long long int64;
typedef unsigned long long uint64;
typedef unsigned char byte;
typedef std::string string;
