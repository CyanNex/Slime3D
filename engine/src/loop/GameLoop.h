#pragma once

#include <loop/TickTask.h>

#include <pch.h>

#define TICKS_PER_SECOND 60

class cGameLoop
{
private:
    // Amount of milliseconds per tick
    const duration<uint, std::milli> tPERIOD = milliseconds((int) std::round((1.0f / TICKS_PER_SECOND) * 1000.0f));

    // Tasks to run every tick
    std::vector<iTickTask*> papTasks;
    std::vector<iTickTask*> papStagingTasks;
    bool pbTasksInvalid = false;

    // If false, the loop will terminate
    bool pbRunning = true;
    bool pbPaused = false;

public:
    // Destroys all the tasks inside this loop
    ~cGameLoop();

    // Starts this GameLoop
    void operator()();

    // Add a task to run every tick
    void AddTask(iTickTask* pTask);
    void RemoveTask(iTickTask* pTask);

    // Stop this GameLoop
    void Stop();

    void SetPaused(bool bPaused);

private:
    // Main loop handling the timing
    void MainLoop();

    // Runs all the tick tasks
    void Tick();

    // Print an error if the duration of the previous tick exceeds a threshold
    void CheckTickTime(time_point<steady_clock> tPrev, time_point<steady_clock> tNow);
};

