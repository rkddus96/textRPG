#include "OpeningScene.h"

#include "LogicHelper.h"
#include "Managers/GameManager.h"
#include "InputReceiver.h"
#include "AudioPlayer.h"
#include "ConstantContainer.h"
#include "Managers/TimerManager.h"

OpeningScene::OpeningScene()
{

}

void OpeningScene::PlayScene()
{
    LogicHelper::SetFixedConsoleSize(Console::CONSOLE_WIDTH, Console::CONSOLE_WIDTH);

    auto& UIManagerInstance = GameManager::GetInstance().GetUIManager();

    UIManagerInstance->PrintUI(ERenderingCanvas::Empty);
    TimerManager::GetInstance();

    LogicHelper::PrintWStringFast(L"시작 전에 창 크기를 충분히 키우신 후 엔터를 입력하여 시작하세요.");

    EKey KeyInput = EKey::UnAvailable;
    while (KeyInput != EKey::Enter)
    {
        KeyInput = InputReceiver::ChatchInput();
    }

    const FASKIIArtContainer& TitleArtContainer = GameManager::GetInstance().GetAssetHandler()->GetASKIIArtContainer(EArtList::Title);
    UIManagerInstance->SetOpeningCanvasTitleArt(10, 10, TitleArtContainer.ArtLines, false);

    const FASKIIArtContainer& BacgroundArtContainer = GameManager::GetInstance().GetAssetHandler()->GetASKIIArtContainer(EArtList::Castle2);
    UIManagerInstance->SetOpeningCanvasBackgroundArt(2, 65, BacgroundArtContainer.ArtLines);
 
    KeyInput = EKey::UnAvailable;
    while (KeyInput != EKey::Enter)
    {
        KeyInput = InputReceiver::ChatchInput();
    }
    
    return;
}

OpeningScene::~OpeningScene()
{
}


