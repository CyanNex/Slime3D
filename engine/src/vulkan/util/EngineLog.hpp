#pragma once

#include <iostream>

#ifndef NDEBUG

#include <pch.hpp>
#include <chrono>
#include <mutex>

using namespace std::chrono;

std::mutex _tEngineLog_Mutex;
steady_clock::time_point _tEngineLog_StartTime = steady_clock::now();

#define _ENGINE_LOG_WARNING_PREFIX "[WARNING] "
#define _ENGINE_LOG_ERROR_PREFIX   "[ERROR] "
#define _ENGINE_LOG_TIME_SINCE_START (duration_cast<milliseconds>(steady_clock::now() - _tEngineLog_StartTime).count())

#define _ENGINE_LOG_RAW_LOG(out, message) \
    _tEngineLog_Mutex.lock();\
    out << "[" << _ENGINE_LOG_TIME_SINCE_START << "] [" << _EngineLog_GetCurrentFileName(__FILE__) << "]: " << message << std::endl;\
    _tEngineLog_Mutex.unlock()\

#define ENGINE_LOG(message) {_ENGINE_LOG_RAW_LOG(std::cout, message);}
#define ENGINE_WARN(message) {_ENGINE_LOG_RAW_LOG(std::cout, _ENGINE_LOG_WARNING_PREFIX << message);}
#define ENGINE_ERROR(message, ex) {_ENGINE_LOG_RAW_LOG(std::cerr, _ENGINE_LOG_ERROR_PREFIX << message << ": " << ex.what()); throw ex;}

#define CURRENT_CLASS_NAME (&typeid(*this).name()[3])

std::string _EngineLog_GetCurrentFileName(const std::string& sPath)
{
    uint uiIndex;
    for (uiIndex = (uint) sPath.size(); uiIndex > 0; uiIndex--)
    {
        if (sPath[uiIndex - 1] == '\\' || sPath[uiIndex - 1] == '/') break;
    }
    std::string sResult = sPath.substr(uiIndex);
    return sResult.substr(0, sResult.length() - 4);
}

#else // NDEBUG
#define CURRENT_CLASS_NAME ("")
#define ENGINE_WARN(message) (void())
#define ENGINE_LOG(message) (void())
#define ENGINE_ERROR(message, ex) (std::cerr << _ENGINE_LOG_ERROR_PREFIX << message << ": " << ex.what() << std::endl)
#endif
