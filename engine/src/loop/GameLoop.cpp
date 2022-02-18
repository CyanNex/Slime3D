#include <loop/GameLoop.h>
#include <util/EngineLog.h>

cGameLoop::~cGameLoop() = default;

void cGameLoop::operator()()
{
    pbRunning = true;
    MainLoop();
}

void cGameLoop::AddTask(iTickTask* pTask)
{
    papStagingTasks.push_back(pTask);
    pbTasksInvalid = true;

    ENGINE_LOG("Added new task to game loop");
}

void cGameLoop::RemoveTask(iTickTask* pTask)
{
    for (auto it = papStagingTasks.begin(); it < papStagingTasks.end(); it++)
    {
        if (*it == pTask)
        {
            papStagingTasks.erase(it);
            pbTasksInvalid = true;
            break;
        }
    }
}

void cGameLoop::Stop()
{
    pbRunning = false;
}

void cGameLoop::SetPaused(bool bPaused)
{
    pbPaused = bPaused;
}

void cGameLoop::MainLoop()
{
    // tNext is the time at which the next tick should start
    time_point tNext = steady_clock::now();

    // tPrev is the time when the last tick started
    time_point tPrev = tNext - tPERIOD;

    ENGINE_LOG("Game loop started");

    while (pbRunning)
    {
        // Run tick time checks
        time_point tNow = steady_clock::now();
        CheckTickTime(tPrev, tNow);
        tPrev = tNow;

        if (!pbPaused)
        {
            // Run all the tick tasks
            Tick();
        }

        if (pbTasksInvalid)
        {
            papTasks.clear();
            for (iTickTask* pTask : papStagingTasks)
            {
                papTasks.push_back(pTask);
            }
            pbTasksInvalid = false;
        }

        // The next tick should start PERIOD milliseconds after the last one
        tNext += tPERIOD;
        std::this_thread::sleep_until(tNext);
    }

    ENGINE_LOG("Game loop stopped");
}

void cGameLoop::Tick()
{
    // Run all the tick tasks
    for (iTickTask* pTask : papTasks)
    {
        pTask->Tick();
    }
}

void cGameLoop::CheckTickTime(time_point<steady_clock> tPrev, time_point<steady_clock> tNow)
{
    const uint uiPERIOD_COUNT = tPERIOD.count();

    // Calculate the time this tick took
    uint uiTickTime = (uint) round < milliseconds > (tNow - tPrev).count();

    // If the time exceeds a threshold, print a warning
    if (uiTickTime > uiPERIOD_COUNT && uiTickTime - uiPERIOD_COUNT > 2)
    {
        ENGINE_WARN("Tick time of " << uiTickTime << "ms " << "exceeds period of " << uiPERIOD_COUNT
                                    << "ms " << "(" << TICKS_PER_SECOND << " tps) significantly!");
    }
}
