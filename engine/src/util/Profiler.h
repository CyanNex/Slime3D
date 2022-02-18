#pragma once

#include <pch.h>
#include <chrono>

#ifndef NDEBUG
#define START_TIMING(name) (cProfiler::poInstance.StartTiming(name))
#define STOP_TIMING(name) (cProfiler::poInstance.StopTiming(name))
#else
#define START_TIMING(name) (void())
#define STOP_TIMING(name) (void())
#endif

using namespace std::chrono;

typedef time_point<steady_clock, nanoseconds> tTimePoint;
typedef steady_clock tClock;

class cProfiler
{
public:
    static cProfiler poInstance;

private:
    tTimePoint ptStartTime = tClock::now();
    uint puiFrameCount = 0;

    uint puiFramesPerSecond = 0;

    std::map<string, steady_clock::time_point> pmtTimings;

public:
    void Update();

    uint GetFramesPerSecond();
    float GetFrameTime();

#ifndef NDEBUG
    void StartTiming(const string& sName);
    uint StopTiming(const string& sName);
#endif
};
