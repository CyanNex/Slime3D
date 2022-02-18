#include <util/EngineLog.h>
#include <mutex>
#include <chrono>

std::mutex cEngineLog::Mutex;

std::string cEngineLog::GetCurrentFileName(const std::string& sPath)
{
    uint uiIndex;
    for (uiIndex = (uint) sPath.size(); uiIndex > 0; uiIndex--)
    {
        if (sPath[uiIndex - 1] == '\\' || sPath[uiIndex - 1] == '/') break;
    }
    std::string sResult = sPath.substr(uiIndex);
    return sResult.substr(0, sResult.length() - 4);
}

static steady_clock::time_point EngineLog_StartTime = steady_clock::now();

ulong cEngineLog::TimeSinceStart()
{
    return duration_cast<milliseconds>(steady_clock::now() - EngineLog_StartTime).count();
}
