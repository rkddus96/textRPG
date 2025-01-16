#include "OpeningScene.h"

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

    AudioPlayer::Play(AudioPath::MAIN_BGM, 0.4f);
    const FASCIIArtContainer& TitleArtContainer = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Title);
    UIManagerInstance->SetOpeningCanvasTitleArt(14, 8, TitleArtContainer, false);

    const FASCIIArtContainer& BacgroundArtContainer = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Castle2);
    UIManagerInstance->SetOpeningCanvasBackgroundArt(2, 65, BacgroundArtContainer.ArtLines);
 
    KeyInput = EKey::UnAvailable;
    while (KeyInput != EKey::Enter)
    {
        KeyInput = InputReceiver::ChatchInput();
    }

    AudioPlayer::StopAll();
    PlayOpeningPrologue();
    return;
}

OpeningScene::~OpeningScene()
{
}

void OpeningScene::PlayOpeningPrologue()
{
    AudioPlayer::Play(AudioPath::RESULT, 0.4f);

    const std::wstring WCharacterName = LogicHelper::StringToWString(Character::GetInstance().GetName());
    auto& UIManagerInstance = GameManager::GetInstance().GetUIManager();

    UIManagerInstance->SetOpeningCanvasLayerHide(true, EOpeningCanvasLayer::Title, false);
    UIManagerInstance->SetOpeningCanvasLayerHide(true, EOpeningCanvasLayer::BackgroundArt, false);
    UIManagerInstance->SetOpeningCanvasLayerHide(true, EOpeningCanvasLayer::PressEnterKeyToStart, false);
    FStoryTextContainer StoryText;

    //L"숲속 마을 에르발트는 왕국에서 멀리 떨어진 평화로운 곳이다.";
    //L"플레이어(이름은 게임 시작 시 입력)가 어린 시절부터 함께 자라온 소꿉친구 **엘라(Ella)**와 서로 깊은 애정을 키워왔다.";
    std::wstring Text = WCharacterName + L"가 어린 시절부터 함께 자라온 소꿉친구 엘라와";

    StoryText.AddTextLine(L"숲속 마을 에르발트는 솔반드리아 왕국에서 멀리 떨어진 평화로운 곳이다.");
    StoryText.AddTextLine(Text);
    StoryText.AddTextLine(L"서로 깊은 애정을 키워왔다.");
    AudioPlayer::Play(AudioPath::BOOK);

    UIManagerInstance->DrawOpeningCanvasPrologue(StoryText);

    EKey KeyInput = EKey::UnAvailable;
    while (KeyInput != EKey::Enter)
    {
        KeyInput = InputReceiver::ChatchInput();
    }

    StoryText.StoryTextLines.resize(0);

    StoryText.AddTextLine(L"두 사람은 언젠가 작은 집을 지어 함께 살아가길 꿈꾸며");
    StoryText.AddTextLine(L"행복한 나날을 보내고 있었다.");
    StoryText.AddTextLine(L" ");
    UIManagerInstance->DrawOpeningCanvasPrologue(StoryText);

    AudioPlayer::Play(AudioPath::BOOK);

    KeyInput = EKey::UnAvailable;
    while (KeyInput != EKey::Enter)
    {
        KeyInput = InputReceiver::ChatchInput();
    }

    StoryText.StoryTextLines.resize(0);

    StoryText.AddTextLine(L"하지만 어느 날, 왕국의 병사들이 마을을 급습해 모든 여성을 끌고 갔다.");
    StoryText.AddTextLine(L"병사들은 이유를 묻는 마을 주민들에게");
    StoryText.AddTextLine(L"\"왕실의 명령이다\"라는 말만 남기고 사라졌다.");
    UIManagerInstance->DrawOpeningCanvasPrologue(StoryText);

    AudioPlayer::Play(AudioPath::BOOK);

    KeyInput = EKey::UnAvailable;
    while (KeyInput != EKey::Enter)
    {
        KeyInput = InputReceiver::ChatchInput();
    }

    StoryText.StoryTextLines.resize(0);

    StoryText.AddTextLine(L"엘라가 끌려가는 모습을 지켜본 플레이어는 깊은 절망과 분노를 느끼며,");
    StoryText.AddTextLine(L"그녀를 되찾기 위해 모험을 떠나기로 결심한다.");
    StoryText.AddTextLine(L" ");
    UIManagerInstance->DrawOpeningCanvasPrologue(StoryText);

    AudioPlayer::Play(AudioPath::BOOK);

    KeyInput = EKey::UnAvailable;
    while (KeyInput != EKey::Enter)
    {
        KeyInput = InputReceiver::ChatchInput();
    }
}


