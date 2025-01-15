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

    const FASCIIArtContainer& TitleArtContainer = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Title);
    UIManagerInstance->SetOpeningCanvasTitleArt(10, 10, TitleArtContainer.ArtLines, false);

    const FASCIIArtContainer& BacgroundArtContainer = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Castle2);
    UIManagerInstance->SetOpeningCanvasBackgroundArt(2, 65, BacgroundArtContainer.ArtLines);
 
    KeyInput = EKey::UnAvailable;
    while (KeyInput != EKey::Enter)
    {
        KeyInput = InputReceiver::ChatchInput();
    }

    PlayOpeningPrologue();
    
    return;
}

OpeningScene::~OpeningScene()
{
}

void OpeningScene::PlayOpeningPrologue()
{
    auto& UIManagerInstance = GameManager::GetInstance().GetUIManager();

    UIManagerInstance->SetOpeningCanvasLayerHide(true, EOpeningCanvasLayer::Title, false);
    UIManagerInstance->SetOpeningCanvasLayerHide(true, EOpeningCanvasLayer::BackgroundArt, false);
    UIManagerInstance->SetOpeningCanvasLayerHide(true, EOpeningCanvasLayer::PressEnterKeyToStart, false);
    FStoryTextContainer StoryText;

    StoryText.AddTextLine(L"대충 스토리..........");
    StoryText.AddTextLine(L"대충 스토리..........");
    StoryText.AddTextLine(L"대충 스토리..........");
    StoryText.AddTextLine(L"대충 스토리..........");
    StoryText.AddTextLine(L"대충 스토리..........");
    StoryText.AddTextLine(L"대충 스토리..........");
    StoryText.AddTextLine(L"대충 스토리..........");
    UIManagerInstance->DrawOpeningCanvasPrologue(StoryText);

    EKey KeyInput = EKey::UnAvailable;
    while (KeyInput != EKey::Enter)
    {
        KeyInput = InputReceiver::ChatchInput();
    }

    StoryText.StoryTextLines.resize(0);

    StoryText.AddTextLine(L"대충 스토리........22..");
    StoryText.AddTextLine(L"대충 스토리..........");
    StoryText.AddTextLine(L"대충 스토리....2......");
    StoryText.AddTextLine(L"대충 스토리..........");
    StoryText.AddTextLine(L"대충 스토리......22....");
    StoryText.AddTextLine(L"대충 스토리..........");
    StoryText.AddTextLine(L"대충 스토리..........");
    UIManagerInstance->DrawOpeningCanvasPrologue(StoryText);

    KeyInput = EKey::UnAvailable;
    while (KeyInput != EKey::Enter)
    {
        KeyInput = InputReceiver::ChatchInput();
    }

    StoryText.StoryTextLines.resize(0);

    StoryText.AddTextLine(L"대충 스토리..........");
    StoryText.AddTextLine(L"대충 스토리..........");
    StoryText.AddTextLine(L"대충 스토리....33......");
    StoryText.AddTextLine(L"대충 스토리..........");
    StoryText.AddTextLine(L"대충 스토리..........");
    StoryText.AddTextLine(L"대충 스토리....3......");
    StoryText.AddTextLine(L"대충 스토리..........");
    UIManagerInstance->DrawOpeningCanvasPrologue(StoryText);

    KeyInput = EKey::UnAvailable;
    while (KeyInput != EKey::Enter)
    {
        KeyInput = InputReceiver::ChatchInput();
    }

    StoryText.StoryTextLines.resize(0);

    StoryText.AddTextLine(L"대충 스토리..........");
    StoryText.AddTextLine(L"대충 스토리..........");
    StoryText.AddTextLine(L"대충 스토리...44.......");
    StoryText.AddTextLine(L"대충 스토리..........");
    StoryText.AddTextLine(L"대충 스토리..........");
    StoryText.AddTextLine(L"대충 스토리....44......");
    StoryText.AddTextLine(L"대충 스토리..........");
    UIManagerInstance->DrawOpeningCanvasPrologue(StoryText);

    KeyInput = EKey::UnAvailable;
    while (KeyInput != EKey::Enter)
    {
        KeyInput = InputReceiver::ChatchInput();
    }
}


