#include <iostream>
#include "LogicHelper.h"
#include "Managers/GameManager.h"
#include "OpeningScene.h"
#include "TileMapScene.h"
#include "ConstantContainer.h"
#include "AudioPlayer.h"
#include "Character.h"
#include "Managers/TimerManager.h"
#include "Managers/UIManager.h"
#include "EndingScene.h"

int main()
{
    OpeningScene Scene;
    Scene.PlayScene();

    TileMapScene TileScene;
    TileScene.PlayScene();

    EndingScene().PlayScene();

    TimerManager::GetInstance().TerminateThread();
    return 0;
}