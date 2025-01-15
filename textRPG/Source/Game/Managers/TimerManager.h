#pragma once

#include <functional>
#include <list>
#include <queue>
#include <iostream>
#include <thread>

struct TimerHandler
{
public:

    TimerHandler(float startTime, float interval, int repeatNumber, const std::function<void()>& function, bool isActive)
    {
        StartTime = startTime;
        initialStartTime = startTime;
        Interval = interval;
        RepeatNumber = repeatNumber;
        initialRepeatNumber = repeatNumber;
        Function = function;
        this->isActive = isActive;
        isStayingActive = false;
        isPaused = false;
        ElapsedTime = 0;
    }

    /// <summary>
    /// it means time until starting first run. if StartTime == -1, timemr dont use first run..
    /// </summary>
    float StartTime;
    float Interval;

    /// <summary>
    /// it except first run. for example, RepeatNumber == 0, Active Once, RepeatNumber == 1, Active Twice.
    /// if RepeatNumber == -1, repeat infinitely until calling ClearTimer
    /// </summary>
    int RepeatNumber;
    float ElapsedTime;
    std::function<void()> Function;

    /// <summary>
    /// if true, this timerHandler is always active.
    /// but when timerHanlder is done, timerHanlder is paused.
    /// </summary>
    bool GetIsStayingActive()
    {
        return isStayingActive;
    }

    void SetIsStayingActive(bool NewIsStayingActive)
    {
        isStayingActive = NewIsStayingActive;
    }

    bool GetIsActive()
    {
        return isActive;
    }

    void SetIsActive(bool NewIsSetActive)
    {
        isActive = NewIsSetActive;
    }

    bool GetIsPaused()
    {
        return isPaused;
    }

    void SetIsPaused(bool NewIsPaused)
    {
        isPaused = NewIsPaused;
    }

    void RestartTimer()
    {
        ElapsedTime = 0;
        RepeatNumber = initialRepeatNumber;
        StartTime = initialStartTime;
        isActive = true;
        isPaused = false;
    }

    void ClearTimer()
    {
        StartTime = 0;
        Interval = 0;
        RepeatNumber = 0;
        ElapsedTime = 0;

        isActive = false;
        isStayingActive = false;
        isPaused = false;
        initialRepeatNumber = 0;
        initialStartTime = 0;
    }

    void ResetTimer(float startTime, float interval, int repeatNumber, const std::function<void()>& function, bool isActive)
    {
        StartTime = startTime;
        initialStartTime = startTime;
        Interval = interval;
        RepeatNumber = repeatNumber;
        initialRepeatNumber = repeatNumber;
        Function = function;
        this->isActive = isActive;
        isStayingActive = false;
        isPaused = false;
    }

private:

    bool isActive;
    bool isStayingActive;
    bool isPaused;

    float initialStartTime;
    int initialRepeatNumber;
};

class TimerManager
{
public:

    static TimerManager& GetInstance()
    {
        // staitc 변수로 선언함으로서, instance 뱐수는 한번만 초기화되고, 프로그램 수명 내내 지속됨.
        // 특히 C++11부터 thread-safe 변수 초기화가 보장됨.
        static TimerManager Instance;
        return Instance;
    }

public:

    std::shared_ptr<TimerHandler> SetTimer(float startTime, float interval, int repeatNumber, std::function<void()> function, bool isActive);

    void TerminateThread();

public:

    std::function<void(double)> OnTickForUIDelegate;
    std::function<void(double)> OnTickForAudioPlayer;

private:

    TimerManager();

    TimerManager(const TimerManager&) = delete;
    TimerManager& operator=(const TimerManager&) = delete;
    TimerManager(TimerManager&&) = delete;
    TimerManager& operator=(TimerManager&&) = delete;

    ~TimerManager();

    void RunTimerThread();


    void Tick(float DeltaTime);

    void ManageTimers(double DeltaTime);

    void Dispose();
private:

    std::list<std::shared_ptr<TimerHandler>> ActivatedTimerHandlers;
    std::queue <std::shared_ptr<TimerHandler>> DeactivatedTimerHandlers;

    double PreviousTickTime;

    std::thread TimerThread;

    bool bIsTerminated;
};
