#include <util/Profiler.h>
#include <util/EngineLog.h>

#define ENABLE_FPS_COUNT

using namespace std::chrono;

cProfiler cProfiler::poInstance;

void cProfiler::Update()
{
    puiFrameCount++;

    tTimePoint tNow = tClock::now();
    float fDelta = duration<float, seconds::period>(tNow - ptStartTime).count();

    if (fDelta >= 1)
    {
        puiFramesPerSecond = puiFrameCount;

#ifdef ENABLE_FPS_COUNT
        ENGINE_LOG(GetFramesPerSecond() << " fps (avg " << GetFrameTime() << "ms)");
#endif

        ptStartTime = tNow;
        puiFrameCount = 0;
    }
}

uint cProfiler::GetFramesPerSecond()
{
    return puiFramesPerSecond;
}

float cProfiler::GetFrameTime()
{
    return 1000.0f / float(puiFramesPerSecond);
}

#ifndef NDEBUG

void cProfiler::StartTiming(const string& sName)
{
    pmtTimings[sName] = steady_clock::now();
}

uint cProfiler::StopTiming(const string& sName)
{
    uint duration = (uint) (duration_cast<milliseconds>(steady_clock::now() - pmtTimings[sName]).count());
    pmtTimings.erase(sName);
    return duration;
}

#endif
