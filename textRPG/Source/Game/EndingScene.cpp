#include "EndingScene.h"
#include "Managers/GameManager.h"
#include "Character.h"
#include "AudioPlayer.h"

EndingScene::EndingScene()
{
}

EndingScene::~EndingScene()
{
}

void EndingScene::PlayScene()
{
    GameManager& GameManagerInstance = GameManager::GetInstance();
    Character& CharacterInstance = Character::GetInstance();

    if (CharacterInstance.IsDead() && GameManagerInstance.IsClearGame() == false)
    {
        GameManagerInstance.GetUIManager()->ShowGameOverScene();
    }
    else if (CharacterInstance.IsDead() == false && GameManagerInstance.IsSpecialEventActivated() == false && GameManagerInstance.IsClearGame())
    {
        PlayNormalEndingEpilogue();
    }
    else if (CharacterInstance.IsDead() == false && GameManagerInstance.IsSpecialEventActivated() && GameManagerInstance.IsClearGame())
    {
        PlayTrueEndingEpilogue();
    }
}

void EndingScene::PlayNormalEndingEpilogue()
{
    AudioPlayer::Play(AudioPath::RESULT, 0.4f);

    const std::wstring WCharacterName = LogicHelper::StringToWString(Character::GetInstance().GetName());
    auto& UIManagerInstance = GameManager::GetInstance().GetUIManager();

    UIManagerInstance->SetEndingCanvasLayerHide(true, EEndingCanvasLayer::GameOver, false);
    UIManagerInstance->SetEndingCanvasLayerHide(true, EEndingCanvasLayer::BackgroundArt, false);
    UIManagerInstance->SetEndingCanvasLayerHide(true, EEndingCanvasLayer::ThankYouForPlaying, false);
    FStoryTextContainer StoryText;

    std::wstring Text = WCharacterName + L"는 리안나를 외면했기 때문에";

    StoryText.AddTextLine(Text);
    StoryText.AddTextLine(L"마왕의 존재를 알지 못한 채 엘라를 데리고 성을 떠난다.");
    StoryText.AddTextLine(L"고향으로 돌아온 두 사람은 평화로운 일상을 보내지만");
    StoryText.AddTextLine(L"마음 한구석에는 미묘한 불안감이 남아 있다.");
    AudioPlayer::Play(AudioPath::BOOK);

    UIManagerInstance->DrawEndingCanvasPrologue(StoryText);

    EKey KeyInput = EKey::UnAvailable;
    while (KeyInput != EKey::Enter)
    {
        KeyInput = InputReceiver::ChatchInput();
    }

    StoryText.StoryTextLines.resize(0);

    StoryText.AddTextLine(" ");
    StoryText.AddTextLine(L"정말 이게 끝일까 ? 왕국이 다시 찾아오지 않을까?");
    StoryText.AddTextLine(L"아니면 더 큰 위험이 도사리고 있는 건 아닐까?");
    StoryText.AddTextLine(" ");
    
    UIManagerInstance->DrawEndingCanvasPrologue(StoryText);

    AudioPlayer::Play(AudioPath::BOOK);

    KeyInput = EKey::UnAvailable;
    while (KeyInput != EKey::Enter)
    {
        KeyInput = InputReceiver::ChatchInput();
    }

    StoryText.StoryTextLines.resize(0);

    StoryText.AddTextLine(" ");
    StoryText.AddTextLine(L"하지만 이 두려움은 일상 속에서 묻혀가며,");
    StoryText.AddTextLine(L"엔딩은 두 사람이 행복한 미소를 짓는 장면으로 마무리된다.");
    StoryText.AddTextLine(" ");
    UIManagerInstance->DrawEndingCanvasPrologue(StoryText);

    AudioPlayer::Play(AudioPath::BOOK);

    KeyInput = EKey::UnAvailable;
    while (KeyInput != EKey::Enter)
    {
        KeyInput = InputReceiver::ChatchInput();
    }
}

void EndingScene::PlayTrueEndingEpilogue()
{
    AudioPlayer::Play(AudioPath::RESULT, 0.4f);

    const std::wstring WCharacterName = LogicHelper::StringToWString(Character::GetInstance().GetName());
    auto& UIManagerInstance = GameManager::GetInstance().GetUIManager();

    UIManagerInstance->SetEndingCanvasLayerHide(true, EEndingCanvasLayer::GameOver, false);
    UIManagerInstance->SetEndingCanvasLayerHide(true, EEndingCanvasLayer::BackgroundArt, false);
    UIManagerInstance->SetEndingCanvasLayerHide(true, EEndingCanvasLayer::ThankYouForPlaying, false);
    FStoryTextContainer StoryText;

    //L"숲속 마을 에르발트는 왕국에서 멀리 떨어진 평화로운 곳이다.";
    //L"플레이어(이름은 게임 시작 시 입력)가 어린 시절부터 함께 자라온 소꿉친구 **엘라(Ella)**와 서로 깊은 애정을 키워왔다.";
    std::wstring Text = WCharacterName + L"와 리안나는 마왕이 부활하려는 순간에 도착한다.";

    StoryText.AddTextLine(Text);
    StoryText.AddTextLine(L"추종자들과의 치열한 전투 끝에 마왕과 대면하며,");
    StoryText.AddTextLine(L"리안나가 전력을 다해 플레이어를 지원한다.");
    AudioPlayer::Play(AudioPath::BOOK);

    UIManagerInstance->DrawEndingCanvasPrologue(StoryText);

    EKey KeyInput = EKey::UnAvailable;
    while (KeyInput != EKey::Enter)
    {
        KeyInput = InputReceiver::ChatchInput();
    }

    StoryText.StoryTextLines.resize(0);

    StoryText.AddTextLine(L"마왕을 처치한 뒤, 리안나는 평화가 찾아온 세상을 보며 웃음을 짓는다.");
    StoryText.AddTextLine(L" ");
    StoryText.AddTextLine(L" ");
    UIManagerInstance->DrawEndingCanvasPrologue(StoryText);

    AudioPlayer::Play(AudioPath::BOOK);

    KeyInput = EKey::UnAvailable;
    while (KeyInput != EKey::Enter)
    {
        KeyInput = InputReceiver::ChatchInput();
    }

    StoryText.StoryTextLines.resize(0);
    
    StoryText.AddTextLine(L" ");
    StoryText.AddTextLine(L"리안나: \"네가 아니었으면 이 모든 걸 끝낼 수 없었을 거야.정말 고마워.\"");
    StoryText.AddTextLine(L" ");
    UIManagerInstance->DrawEndingCanvasPrologue(StoryText);

    AudioPlayer::Play(AudioPath::BOOK);

    KeyInput = EKey::UnAvailable;
    while (KeyInput != EKey::Enter)
    {
        KeyInput = InputReceiver::ChatchInput();
    }

    StoryText.StoryTextLines.resize(0);

    Text = WCharacterName + L"는 엘라와 함께 고향으로 돌아가 평화로운 나날을 보낸다.";

    StoryText.AddTextLine(Text);
    StoryText.AddTextLine(L"엔딩 화면에는 두 사람이 행복하게 웃으며 손을 잡고 있는 모습이 비친다.");
    StoryText.AddTextLine(L" ");
    UIManagerInstance->DrawEndingCanvasPrologue(StoryText);

    AudioPlayer::Play(AudioPath::BOOK);

    KeyInput = EKey::UnAvailable;
    while (KeyInput != EKey::Enter)
    {
        KeyInput = InputReceiver::ChatchInput();
    }
}
