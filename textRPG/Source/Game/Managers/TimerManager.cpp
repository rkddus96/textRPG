#include "TimerManager.h"
#include "../LogicHelper.h"

TimerManager::TimerManager() :
    PreviousTickTime(LogicHelper::GetTimeSecond()),
    bIsTerminated(false)
{
	TimerThread = std::thread(&TimerManager::RunTimerThread, this);
}

void TimerManager::RunTimerThread()
{
	try
	{
		while (bIsTerminated == false)
		{
			float CurrentTime = LogicHelper::GetTimeSecond();
			float DeltaTime = CurrentTime - PreviousTickTime;
			PreviousTickTime = CurrentTime;
			Tick(DeltaTime);

			std::this_thread::sleep_for(std::chrono::milliseconds(34));
		}
	}
	catch (std::string Error)
	{
		std::cout << "Error : " << Error << std::endl;
		Dispose();
		throw;
	}
}

void TimerManager::Tick(float DeltaTime)
{
    ManageTimers(DeltaTime);

    OnTickForUIDelegate(DeltaTime);
}

void TimerManager::ManageTimers(double DeltaTime)
{
    auto node = ActivatedTimerHandlers.begin();

    while (node != ActivatedTimerHandlers.end())
    {
        std::shared_ptr<TimerHandler> handler = *node;

        if (handler->GetIsPaused())
        {
            node++;
            continue;
        }

        bool isFirstRunEnded = (handler->StartTime == -1);
        if (isFirstRunEnded == false)
        {
            if (handler->StartTime <= handler->ElapsedTime)
            {
                handler->StartTime = -1;
                handler->ElapsedTime = 0;
                handler->Function();
            }
        }
        else if (handler->RepeatNumber > 0 || handler->RepeatNumber == -1)
        {
            if (handler->Interval <= handler->ElapsedTime)
            {
                if (handler->RepeatNumber > 0)
                {
                    handler->RepeatNumber--;
                }

                handler->ElapsedTime = 0;
                handler->Function();
            }
        }
        else
        {
            if (handler->GetIsStayingActive())
            {
                handler->SetIsPaused(true);
                node++;
                continue;
            }

            handler->SetIsActive(false);
            DeactivatedTimerHandlers.push(handler);

            if (std::next(node) == ActivatedTimerHandlers.end())
            {
                ActivatedTimerHandlers.erase(node);
                break;
            }
            else
            {
                node++;
                ActivatedTimerHandlers.erase(std::prev(node));
            }

            continue;
        }

        handler->ElapsedTime += (float)DeltaTime;
        node++;
    }
}

std::shared_ptr<TimerHandler> TimerManager::SetTimer(float startTime, float interval, int repeatNumber, std::function<void()> function, bool isActive)
{
    std::shared_ptr<TimerHandler> timerHandler;

    if (DeactivatedTimerHandlers.size() == 0)
    {
        timerHandler = std::make_shared<TimerHandler>(startTime, interval, repeatNumber, function, isActive);
    }
    else
    {
        timerHandler = DeactivatedTimerHandlers.front();
        DeactivatedTimerHandlers.pop();

        timerHandler->ResetTimer(startTime, interval, repeatNumber, function, isActive);
    }

    ActivatedTimerHandlers.push_back(timerHandler);
    return timerHandler;
}

void TimerManager::TerminateThread()
{
    bIsTerminated = true;
}

void TimerManager::Dispose()
{
	TimerThread.join();
	std::cout << "TimerHandler is Disposed" << std::endl;
}

TimerManager::~TimerManager()
{
	Dispose();
}

