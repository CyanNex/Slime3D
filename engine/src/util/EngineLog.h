#pragma once

#include <iostream>

#ifndef NDEBUG

#include <pch.h>
#include <chrono>
#include <mutex>

#define _ENGINE_LOG_WARNING_PREFIX "[WARNING] "
#define _ENGINE_LOG_ERROR_PREFIX   "[ERROR] "
#define _ENGINE_LOG_TIME_SINCE_START (cEngineLog::TimeSinceStart())

#define _ENGINE_LOG_RAW_LOG(out, message) \
    cEngineLog::Mutex.lock();\
    out << "[" << _ENGINE_LOG_TIME_SINCE_START << "] [" << cEngineLog::GetCurrentFileName(__FILE__) << "]: " << message << std::endl;\
    cEngineLog::Mutex.unlock()\

#define ENGINE_LOG(message) {_ENGINE_LOG_RAW_LOG(std::cout, message);}
#define ENGINE_WARN(message) {_ENGINE_LOG_RAW_LOG(std::cout, _ENGINE_LOG_WARNING_PREFIX << message);}
#define ENGINE_EXCEPT(message, ex) {_ENGINE_LOG_RAW_LOG(std::cerr, _ENGINE_LOG_ERROR_PREFIX << message << ": " << ex.what()); throw ex;}
#define ENGINE_ERROR(message) {_ENGINE_LOG_RAW_LOG(std::cerr, _ENGINE_LOG_ERROR_PREFIX << message);}

#define CURRENT_CLASS_NAME (&typeid(*this).name()[3])

#else // NDEBUG
#define CURRENT_CLASS_NAME ("")
#define ENGINE_WARN(message) (void())
#define ENGINE_LOG(message) (void())
#define ENGINE_EXCEPT(message, ex) (std::cerr << _ENGINE_LOG_ERROR_PREFIX << message << ": " << ex.what() << std::endl)
#endif

class cEngineLog
{
public:
    static std::mutex Mutex;

    static ulong TimeSinceStart();
    static std::string GetCurrentFileName(const std::string& sPath);
};
