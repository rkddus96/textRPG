#include <iostream>
#include "LogicHelper.h"
#include "Managers/GameManager.h"
#include "OpeningScene.h"
#include "TileMapScene.h"
#include "ConstantContainer.h"
#include "AudioPlayer.h"
#include "Character.h"
#include "Managers/TimerManager.h"

int main()
{
    OpeningScene Scene;
    Scene.PlayScene();

    Character::GetInstance();
    
    TileMapScene TileScene;
    TileScene.PlayScene();

    TimerManager::GetInstance().TerminateThread();
    return 0;
}