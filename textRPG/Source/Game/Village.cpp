#include "Village.h"

#include <sstream>
#include "Managers/GameManager.h"
#include "Managers/UIManager.h"
#include "InputReceiver.h"
#include "LogicHelper.h"
#include "Character.h"
#include "Shop.h"

Village::Village(Character& Player, std::shared_ptr<UIManager> ui, EArtList VillageArt)
	:Player(Player), UIManagerInstance(ui), DefualtArt(VillageArt), DefaultMessage(L"마을의 중심에 도착했습니다. 무엇을 하시겠습니까?")
{
}

void Village::Run()
{
	// 정보에 따라 현재 선택지 정보 초기환
	BuildOptions();

	DrawDefaultScene();

	while (!bEndVillage)
	{
		// 이벤트를 발생시킬 수 있을 경우는 이벤트를 발생시키는 추가 선택지가 존재한다.
		EKey KeyInput = InputReceiver::ChatchInput();

		if (KeyMappingMap.find(KeyInput) != KeyMappingMap.end())
		{
			// 해당 Key의 함수를 실행
			KeyMappingMap[KeyInput]();
		}
		else
		{
			// 적합하지 않은 입력은 무시하고 다시 입력을 받는다.
			continue;
		}
		
		// KeyInput으로 해당 씬들을 종료하고 돌아왔으면 다시 초기 화면을 출력한다.
		DrawDefaultScene();
	}

	// 퇴장
}

void Village::DrawDefaultScene()
{
	std::wstring EnterMessage = L"마을의 중심에 도착했습니다. 무엇을 하시겠습니까?";

	// 기본 화면을 출력
	UIManagerInstance->ClearMessageToBasicCanvasEventInfoUI();
	UIManagerInstance->AddMessageToBasicCanvasEventInfoUI(EnterMessage, false);
	UIManagerInstance->AddMessageToBasicCanvasEventInfoUI(DefulatSelectoinMessage, false);
	const FASCIIArtContainer& DefaultArtContainer = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(DefualtArt);
	UIManagerInstance->ChangeBasicCanvasArtImage(DefaultArtContainer, false, ArtOffset.first, ArtOffset.second);
	UIManagerInstance->PrintUI(ERenderingCanvas::Basic);
}

void Village::VisitStore()
{
	std::shared_ptr<Shop> ShopInstance = GameManager::GetInstance().GetShop();
	ShopInstance->ManageShop(Player);
}

void Village::VisitChurch()
{
	const FASCIIArtContainer& DefaultArtContainer = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Church);
	UIManagerInstance->ChangeBasicCanvasArtImage(DefaultArtContainer, false);

	std::wstring ChurchEnterMessage = L"신성한 기도와 차분한 분위기가 당신을 감싸고 있습니다.";
	std::wstring ChurchQuestionMessage = L"회복의 축복을 받으시겠습니까? 비용은 " + std::to_wstring(DefaultHealCharge) + L"골드입니다. Z키로 수락, X키로 거절합니다.";
	std::wstring ChurchHealMessage = L"사제가 두 손을 들어 당신을 축복합니다. 따스한 빛이 몸을 감싸며 상처가 아물기 시작합니다.";
	std::wstring ChurchGoldRejectMessage = L"신의 축복은 모든 이에게 열려있지만, 이곳의 유지에는 헌금이 필요합니다. 골드가 조금 부족한 것 같군요.";
	std::wstring ChurchRejectMessage = L"당신의 선택을 존중합니다. 신의 은총이 함께 하기를 바랍니다. ";

	UIManagerInstance->ClearMessageToBasicCanvasEventInfoUI(false);
	UIManagerInstance->AddMessageToBasicCanvasEventInfoUI(ChurchEnterMessage,false);
	UIManagerInstance->AddMessageToBasicCanvasEventInfoUI(ChurchQuestionMessage, false);
	UIManagerInstance->PrintUI(ERenderingCanvas::Basic);

	EKey KeyInput;
	do {
		KeyInput = InputReceiver::ChatchInput();
	}while(KeyInput != EKey::z && KeyInput != EKey::Z && KeyInput != EKey::X && KeyInput != EKey::x);

	if (KeyInput == EKey::z || KeyInput == EKey::Z)
	{
		int PlayerGold = Player.GetGold();
		// 체력 회복
		if (PlayerGold >= DefaultHealCharge)
		{
			Player.SetGold(PlayerGold - DefaultHealCharge);

			// Restore Health
			Status& PlayerStatus = Player.GetStatus();
			int CurrentHealth = PlayerStatus.GetStat(EStat::CurHp);
			int MaxHealth = PlayerStatus.GetStat(EStat::MaxHp);
			// Calculate Helath Logic
			int FinalHealth = MaxHealth;
			PlayerStatus.SetStat(EStat::CurHp, FinalHealth);

			UIManagerInstance->ClearMessageToBasicCanvasEventInfoUI(false);
			UIManagerInstance->AddMessageToBasicCanvasEventInfoUI(ChurchHealMessage, true);
		}
		// 골드 부족, 거절 메시지 출력
		else
		{
			UIManagerInstance->ClearMessageToBasicCanvasEventInfoUI(false);
			UIManagerInstance->AddMessageToBasicCanvasEventInfoUI(ChurchGoldRejectMessage, true);
		}
	}
	else
	{
		// 거절 메시지
		UIManagerInstance->ClearMessageToBasicCanvasEventInfoUI(false);
		UIManagerInstance->AddMessageToBasicCanvasEventInfoUI(ChurchRejectMessage, true);
	}

	LogicHelper::SleepFor(1000);
}

void Village::VisitEvent()
{
	UIManagerInstance->AddMessageToBasicCanvasEventInfoUI(L"대화");

	EKey KeyInput = InputReceiver::ChatchInput();
}

void Village::Exit()
{
	bEndVillage = true;
}

void Village::BuildOptions()
{
	std::vector<std::wstring> OptionMessages;

	int KeyIndex = static_cast<int>(EKey::Key_1);
	if (bHasShop)
	{
		OptionMessages.push_back(L"상점");
		EKey MappingKey = static_cast<EKey>(KeyIndex++);
		KeyMappingMap[MappingKey] = std::bind(&Village::VisitStore, this);
	}
	if (bHasChurch)
	{
		OptionMessages.push_back(L"교회");
		EKey MappingKey = static_cast<EKey>(KeyIndex++);
		KeyMappingMap[MappingKey] = std::bind(&Village::VisitChurch, this);
	}
	// 현재 사용하지는 않음
	if (bCanTriggerEvent)
	{
		OptionMessages.push_back(L"대화하기");
		EKey MappingKey = static_cast<EKey>(KeyIndex++);
		KeyMappingMap[MappingKey] = std::bind(&Village::VisitEvent, this);
	}
	// 종료는 항상 존재
	{
		OptionMessages.push_back(L"나가기");
		EKey MappingKey = static_cast<EKey>(KeyIndex++);
		KeyMappingMap[MappingKey] = std::bind(&Village::Exit, this);
	}

	DefulatSelectoinMessage = FormatSelectionMessage(OptionMessages);
}

std::wstring Village::FormatSelectionMessage(const std::vector<std::wstring>& OptionTexts) const
{
	std::wstringstream optionStream;
	for (int i = 0; i < OptionTexts.size(); i++)
	{
		if (i != 0)
		{
			optionStream << ", ";
		}
		optionStream << (i + 1) << L". " << OptionTexts[i];
	}

	return optionStream.str();
}