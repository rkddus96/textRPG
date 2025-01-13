#include "MyTestScene.h"

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include "LogicHelper.h"
#include "Managers/GameManager.h"
#include "InputReceiver.h"
#include "AudioPlayer.h"
#include "ConstantContainer.h"
#include "Managers/TimerManager.h"
#include "Character.h"

void MyTestScene::TestMain()
{
    LogicHelper::SetFixedConsoleSize(220, 60);

    Character& MyCharacter = Character::GetInstance();


    auto& UIManagerInstance = GameManager::GetInstance().GetUIManager();
    UIManagerInstance->BindAllDelegate();


    UIManagerInstance->PrintUI(ERenderingCanvas::Empty);
    TimerManager::GetInstance();
    
    EKey KeyInput = InputReceiver::ChatchInput();

    const FASKIIArtContainer& TitleArtContainer = GameManager::GetInstance().GetAssetHandler()->GetASKIIArtContainer(EArtList::Title);
    UIManagerInstance->SetOpeningCanvasTitleArt(20, 80, TitleArtContainer.ArtLines);
    UIManagerInstance->PrintUI(ERenderingCanvas::Opening);

    Character::GetInstance().SetExp(100);
    MyCharacter.LevelUp();

    for (int i = 0; i < 100; ++i)
    {
        KeyInput = InputReceiver::ChatchInput();

        std::wstring NewStr = L"키를 눌렀습니다... : " + std::to_wstring(i);

        UIManagerInstance->AddMessageToBasicCanvasEventInfoUI(NewStr);
        UIManagerInstance->ChangeBasicCanvasStatInfoUI(ETempStatType::Level, LogicHelper::GetRandomNumber(0, 999));
        UIManagerInstance->ChangeBasicCanvasStatInfoUI(ETempStatType::Defence, LogicHelper::GetRandomNumber(0, 999));
        UIManagerInstance->ChangeBasicCanvasStatInfoUI(ETempStatType::Power, LogicHelper::GetRandomNumber(0, 999));
        UIManagerInstance->ChangeBasicCanvasStatInfoUI(ETempStatType::Luck, LogicHelper::GetRandomNumber(0, 999));
        UIManagerInstance->ChangeBasicCanvasStatInfoUI(ETempStatType::Hp, LogicHelper::GetRandomNumber(0, 999));

        const FASKIIArtContainer& ArtContainer = GameManager::GetInstance().GetAssetHandler()->GetASKIIArtContainer((EArtList)LogicHelper::GetRandomNumber(0, 3));
        UIManagerInstance->ChangeBasicCanvasArtImage(ArtContainer.ArtLines);

        UIManagerInstance->OnMinimapUIContentsChanged(
            {
                {(ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6),},
                { (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), },
                {(ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6),},
                {(ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6),},
                {(ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6),},
                {(ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6),},
                {(ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6),},
                {(ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6), (ETempTileType)LogicHelper::GetRandomNumber(0, 6),}
            }
        );

        UIManagerInstance->PrintUI(ERenderingCanvas::Basic);
        AudioPlayer::Play(AudioPath::TEST1, 0.5f);
    }

    TimerManager::GetInstance().TerminateThread();
    return;
}

MyTestScene::MyTestScene()
{
}
