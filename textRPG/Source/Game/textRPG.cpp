#include <iostream>
#include "LogicHelper.h"
#include "Managers/GameManager.h"
#include "OpeningScene.h"
#include "ConstantContainer.h"
#include "AudioPlayer.h"
#include "Character.h"
#include "Managers/TimerManager.h"

int main()
{
    OpeningScene Scene;
    Scene.PlayScene();

    Character::GetInstance();
    

    TimerManager::GetInstance().TerminateThread();
    return 0;
}