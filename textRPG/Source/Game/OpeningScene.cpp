#include "OpeningScene.h"

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

OpeningScene::OpeningScene()
{

}
void OpeningScene::PlayOpening()
{
    LogicHelper::SetFixedConsoleSize(Console::CONSOLE_WIDTH, Console::CONSOLE_WIDTH);

    Character& MyCharacter = Character::GetInstance();


    auto& UIManagerInstance = GameManager::GetInstance().GetUIManager();
    UIManagerInstance->BindAllDelegate();


   UIManagerInstance->PrintUI(ERenderingCanvas::Empty);
    TimerManager::GetInstance();
    
    auto AudioName = AudioPlayer::PlayLoop(AudioPath::TEST1, 0.5);
    const FASKIIArtContainer& InventoryBackgroundImage = GameManager::GetInstance().GetAssetHandler()->GetASKIIArtContainer(EArtList::Test);
    UIManagerInstance->SetInventoryCanvasBackgroundImage(InventoryBackgroundImage);

    EKey KeyInput = InputReceiver::ChatchInput();

    const FASKIIArtContainer& TitleArtContainer = GameManager::GetInstance().GetAssetHandler()->GetASKIIArtContainer(EArtList::Title);
    UIManagerInstance->SetOpeningCanvasTitleArt(10, 10, TitleArtContainer.ArtLines);

    Character::GetInstance().SetExp(100);
    MyCharacter.LevelUp();

    GameManager::GetInstance().GetTileMap()->Move(0, 0);

    for (int i = 0; i < 100; ++i)
    {
        KeyInput = InputReceiver::ChatchInput();
        AudioPlayer::Stop(AudioName);
        std::wstring NewStr = L"키를 눌렀습니다... : " + std::to_wstring(i);

        UIManagerInstance->AddMessageToBasicCanvasEventInfoUI(NewStr);
        UIManagerInstance->ChangeBasicCanvasStatInfoUI(ETempStatType::Level, LogicHelper::GetRandomNumber(0, 999));
        UIManagerInstance->ChangeBasicCanvasStatInfoUI(ETempStatType::Defence, LogicHelper::GetRandomNumber(0, 999));
        UIManagerInstance->ChangeBasicCanvasStatInfoUI(ETempStatType::Power, LogicHelper::GetRandomNumber(0, 999));
        UIManagerInstance->ChangeBasicCanvasStatInfoUI(ETempStatType::Luck, LogicHelper::GetRandomNumber(0, 999));
        UIManagerInstance->ChangeBasicCanvasStatInfoUI(ETempStatType::Hp, LogicHelper::GetRandomNumber(0, 999));

        const FASKIIArtContainer& ArtContainer = GameManager::GetInstance().GetAssetHandler()->GetASKIIArtContainer((EArtList)LogicHelper::GetRandomNumber(0, 22));
        UIManagerInstance->ChangeBasicCanvasArtImage(ArtContainer);

        //UIManagerInstance->PrintUI(ERenderingCanvas::Basic);
        //AudioPlayer::Play(AudioPath::TEST1, 0.5f);
    }

    TimerManager::GetInstance().TerminateThread();
    return;
}

OpeningScene::~OpeningScene()
{
}


