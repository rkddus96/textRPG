#include "UIManager.h"
#include "../RenderingCanvas.h"
#include "../LogicHelper.h"
#include "../RenderingLayer.h"
#include "../ConstantContainer.h"
#include "GameManager.h"
#include "TimerManager.h"
#include <functional>
#include "../Character.h"
#include "../IItem.h"
#include "../Status.h"
#include <algorithm>
#include <Windows.h>
#include "../Creatures/Monster.h"
#include "../IItem.h"

// 매크로 제거
#undef min
#undef max

UIManager::UIManager()
{
	
}

void UIManager::AddRenderingCanvas(ERenderingCanvas CanvasType, const std::shared_ptr<RenderingCanvas> NewRenderingCanvas)
{
	if (RenderingCanvasMap[CanvasType])
	{
		LogicHelper::PrintWStringFast(L"Fail to Add RenderingCanvas");
		return;
	}

	RenderingCanvasMap[CanvasType] = NewRenderingCanvas;
}

void UIManager::PrintUI(ERenderingCanvas CanvasType)
{
	std::shared_ptr<RenderingCanvas> Canvas = RenderingCanvasMap[CanvasType];

	if (Canvas == nullptr)
	{
		LogicHelper::PrintWStringFast(L"UIManager::PrintUI, Fail to Print UI");
		return;
	}

	Canvas->PrintCurrentScreenUI();
}

void UIManager::Init()
{
	MakeEmtpyCanvasUI();
	MakeOpningSceneUI();
	MakeInventorySceneUI();

	int PredictedMinimapWidth = 10;
	int PredictedMinimapHeight = 10;
	MinimapUIContents = std::vector<std::vector<wchar_t>>(PredictedMinimapHeight, std::vector<wchar_t>(PredictedMinimapWidth, L'O'));
	MakeBasicUI();

	MakeEndingSceneUI();
}

void UIManager::MakeEmtpyCanvasUI()
{
	std::shared_ptr<RenderingLayer> EmptyLayer = std::make_shared<RenderingLayer>(0);
	EmptyLayer->ClearLayerFor(L' ');
	EmptyLayer-> CombineUiLines();

	std::shared_ptr<RenderingCanvas> EmptyCanvas = std::make_shared<RenderingCanvas>();

	EmptyCanvas->AddLayer(EmptyLayer);
	AddRenderingCanvas(ERenderingCanvas::Empty, EmptyCanvas);
}

void UIManager::MakeBasicUI()
{
	std::shared_ptr<RenderingLayer> MiniMapContentsLayer = std::make_shared<RenderingLayer>((int)EBasicCanvasLayer::MinimapContents);
	BasicCanvasLayerIdMap[EBasicCanvasLayer::MinimapContents] = MiniMapContentsLayer->GetLayerId();

	//MiniMapContentsLayer->ClearLayerFor(L' ');

	std::shared_ptr<RenderingLayer> ArtLayer = std::make_shared<RenderingLayer>((int)EBasicCanvasLayer::Art, UI::USELESS_CHAR);
	BasicCanvasLayerIdMap[EBasicCanvasLayer::Art] = ArtLayer->GetLayerId();

	std::shared_ptr<RenderingLayer> VfxLayer = std::make_shared<RenderingLayer>((int)EBasicCanvasLayer::Vfx);
	BasicCanvasLayerIdMap[EBasicCanvasLayer::Vfx] = VfxLayer->GetLayerId();

	std::shared_ptr<RenderingLayer> BackgroundBorderLayer = std::make_shared<RenderingLayer>((int)EBasicCanvasLayer::BackgroundBorder);
	BasicCanvasLayerIdMap[EBasicCanvasLayer::BackgroundBorder] = BackgroundBorderLayer->GetLayerId();
	BackgroundBorderLayer->ClearLayerFor(L' ');
	//BackgroundBorderLayer->DrawRectanlge(1, 0, 218, 57);
	BackgroundBorderLayer->DrawRectanlge(UI::BACKGRUOND_BORDER_FIRST_POSITION_X, UI::BACKGROUND_BORDER_FIRST_POSITION_Y, UI::BACKGROUND_BORDER_WIDTH, UI::BACKGROUND_BORDER_HEIGHT);
	BackgroundBorderLayer->CombineUiLines();

	std::shared_ptr<RenderingLayer> MinimapBorderLayer = std::make_shared<RenderingLayer>((int)EBasicCanvasLayer::MinimapBorder);
	BasicCanvasLayerIdMap[EBasicCanvasLayer::MinimapBorder] = MinimapBorderLayer->GetLayerId();

	std::shared_ptr<RenderingLayer> EventInfoUIBorderLayer = std::make_shared<RenderingLayer>((int)EBasicCanvasLayer::EventInfoUIBorder);
	BasicCanvasLayerIdMap[EBasicCanvasLayer::EventInfoUIBorder] = EventInfoUIBorderLayer->GetLayerId();

	//EventInfoUIBorderLayer->DrawRectanlge(51, 2, 214, 6);
	EventInfoUIBorderLayer->DrawRectanlge(UI::EVENT_INFO_UI_BORDER_FIRST_POSITION_X, UI::EVENT_INFO_UI_BORDER_FIRST_POSITION_Y, UI::EVENT_INFO_UI_BORDER_WIDTH, UI::EVENT_INFO_UI_BORDER_HEIGHT);
	EventInfoUIBorderLayer->CombineUiLines();

	std::shared_ptr<RenderingLayer> EventInfoUIContentsLayer = std::make_shared<RenderingLayer>((int)EBasicCanvasLayer::EventInfoUIContents, UI::USELESS_CHAR);
	BasicCanvasLayerIdMap[EBasicCanvasLayer::EventInfoUIContents] = EventInfoUIContentsLayer->GetLayerId();

	EventInfoUIContentsLayer->ClearLayerFor(UI::USELESS_CHAR); // 한글 쓰려면 Layer의 마스크랑 같은 문자로 Clear를 한 번 해줘야 한다........

	std::shared_ptr<RenderingLayer> StatInfoLayer = std::make_shared<RenderingLayer>((int)EBasicCanvasLayer::StatInfo, UI::USELESS_CHAR);
	BasicCanvasLayerIdMap[EBasicCanvasLayer::StatInfo] = StatInfoLayer->GetLayerId();

	StatInfoLayer->ClearLayerFor(UI::USELESS_CHAR);

	std::shared_ptr<RenderingLayer> MonsterInfoLayer = std::make_shared<RenderingLayer>((int)EBasicCanvasLayer::MonsterInfo, UI::USELESS_CHAR);
	BasicCanvasLayerIdMap[EBasicCanvasLayer::MonsterInfo] = StatInfoLayer->GetLayerId();

	StatInfoLayer->ClearLayerFor(UI::USELESS_CHAR);

	std::shared_ptr<RenderingCanvas> BasicCanvas = std::make_shared<RenderingCanvas>();

	BasicCanvas->AddLayer(MiniMapContentsLayer);
	BasicCanvas->AddLayer(BackgroundBorderLayer);
	BasicCanvas->AddLayer(ArtLayer);
	BasicCanvas->AddLayer(MinimapBorderLayer);
	BasicCanvas->AddLayer(EventInfoUIBorderLayer);
	BasicCanvas->AddLayer(EventInfoUIContentsLayer);
	BasicCanvas->AddLayer(StatInfoLayer);

	AddRenderingCanvas(ERenderingCanvas::Basic, BasicCanvas);
}

void UIManager::MakeOpningSceneUI()
{
	std::shared_ptr<RenderingLayer> BackgroundBorderLayer = std::make_shared<RenderingLayer>((int)EOpeningCanvasLayer::BackgroundBorder);
	OpeningCanvasLayerIdMap[EOpeningCanvasLayer::BackgroundBorder] = BackgroundBorderLayer->GetLayerId();

	BackgroundBorderLayer->ClearLayerFor(L' ');
	BackgroundBorderLayer->DrawRectanlge(UI::BACKGRUOND_BORDER_FIRST_POSITION_X, UI::BACKGROUND_BORDER_FIRST_POSITION_Y, UI::BACKGROUND_BORDER_WIDTH, UI::BACKGROUND_BORDER_HEIGHT);
	BackgroundBorderLayer->CombineUiLines();

	std::shared_ptr<RenderingLayer> BackgroundArtLayer = std::make_shared<RenderingLayer>((int)EOpeningCanvasLayer::BackgroundArt, L' ');
	OpeningCanvasLayerIdMap[EOpeningCanvasLayer::BackgroundArt] = BackgroundArtLayer->GetLayerId();

	BackgroundArtLayer->ClearLayerFor(L' ');
	BackgroundArtLayer-> CombineUiLines();

	std::shared_ptr<RenderingLayer> TitleLayer = std::make_shared<RenderingLayer>((int)EOpeningCanvasLayer::Title, UI::USELESS_CHAR);
	OpeningCanvasLayerIdMap[EOpeningCanvasLayer::Title] = TitleLayer->GetLayerId();

	TitleLayer->ClearLayerFor(UI::USELESS_CHAR);

	std::shared_ptr<RenderingLayer> PressEnterKeyToStartLayer = std::make_shared<RenderingLayer>((int)EOpeningCanvasLayer::PressEnterKeyToStart, UI::USELESS_CHAR);
	OpeningCanvasLayerIdMap[EOpeningCanvasLayer::PressEnterKeyToStart] = PressEnterKeyToStartLayer->GetLayerId();

	PressEnterKeyToStartLayer->ClearLayerFor(UI::USELESS_CHAR);
	PressEnterKeyToStartLayer->DrawString(UI::PRESS_ENTER_KEY_TO_START_UI_POSITION_X, UI::PRESS_ENTER_KEY_TO_START_UI_POSITION_Y, L"Press Enter Key To Start Game");
	PressEnterKeyToStartLayer->CombineUiLines();

	std::shared_ptr<RenderingLayer> PrologBackgroundLayer = std::make_shared<RenderingLayer>((int)EOpeningCanvasLayer::PrologBackground, UI::USELESS_CHAR);
	OpeningCanvasLayerIdMap[EOpeningCanvasLayer::PrologBackground] = PrologBackgroundLayer->GetLayerId();

	PrologBackgroundLayer->ClearLayerFor(UI::USELESS_CHAR);
	PrologBackgroundLayer->CombineUiLines();

	std::shared_ptr<RenderingLayer> PrologueTextLayer = std::make_shared<RenderingLayer>((int)EOpeningCanvasLayer::PrologueText, UI::USELESS_CHAR);
	OpeningCanvasLayerIdMap[EOpeningCanvasLayer::PrologueText] = PrologueTextLayer->GetLayerId();

	PrologueTextLayer->ClearLayerFor(UI::USELESS_CHAR);
	PrologueTextLayer->CombineUiLines();
	

	std::shared_ptr<RenderingCanvas> OpeningCanvas = std::make_shared<RenderingCanvas>();
	OpeningCanvas->AddLayer(BackgroundArtLayer);
	OpeningCanvas->AddLayer(TitleLayer);
	OpeningCanvas->AddLayer(BackgroundBorderLayer);
	OpeningCanvas->AddLayer(PressEnterKeyToStartLayer);
	OpeningCanvas->AddLayer(PrologBackgroundLayer);
	OpeningCanvas->AddLayer(PrologueTextLayer);

	AddRenderingCanvas(ERenderingCanvas::Opening, OpeningCanvas);
}

void UIManager::MakeEndingSceneUI()
{
	std::shared_ptr<RenderingLayer> BackgroundLayer = std::make_shared<RenderingLayer>((int)EEndingCanvasLayer::Background);
	EndiningCanvasLayerIdMap[EEndingCanvasLayer::Background] = BackgroundLayer->GetLayerId();

	BackgroundLayer->ClearLayerFor(L' ');
	BackgroundLayer->CombineUiLines();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::shared_ptr<RenderingLayer> BackgrundArtLayer = std::make_shared<RenderingLayer>((int)EEndingCanvasLayer::BackgroundArt, UI::USELESS_CHAR);
	EndiningCanvasLayerIdMap[EEndingCanvasLayer::BackgroundArt] = BackgrundArtLayer->GetLayerId();

	BackgrundArtLayer->ClearLayerFor(UI::USELESS_CHAR);
	BackgrundArtLayer->CombineUiLines();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::shared_ptr<RenderingLayer> GameOverLayer = std::make_shared<RenderingLayer>((int)EEndingCanvasLayer::GameOver, UI::USELESS_CHAR);
	EndiningCanvasLayerIdMap[EEndingCanvasLayer::GameOver] = GameOverLayer->GetLayerId();

	GameOverLayer->ClearLayerFor(UI::USELESS_CHAR);
	
	const FASCIIArtContainer& SkeletonHeadArt = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::SkeletonHead);
	int PositionX = UI::CENTER_OF_UI_X - SkeletonHeadArt.GetHeight() / 2;
	int PositionY = UI::CENTER_OF_UI_Y - SkeletonHeadArt.GetWidth() / 2;

	GameOverLayer->DrawSurface(PositionX, PositionY, SkeletonHeadArt.ArtLines);

	const FASCIIArtContainer& GameOverArt = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::GameOver);
	PositionX = UI::CENTER_OF_UI_X - GameOverArt.GetHeight() / 2 + 20;
	PositionY = UI::CENTER_OF_UI_Y - GameOverArt.GetWidth() / 2;

	GameOverLayer->DrawSurface(PositionX, PositionY, GameOverArt.ArtLines);
	GameOverLayer->CombineUiLines();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::shared_ptr<RenderingLayer> ThankYouForPlayingLayer = std::make_shared<RenderingLayer>((int)EEndingCanvasLayer::ThankYouForPlaying, UI::USELESS_CHAR);
	EndiningCanvasLayerIdMap[EEndingCanvasLayer::ThankYouForPlaying] = ThankYouForPlayingLayer->GetLayerId();

	ThankYouForPlayingLayer->ClearLayerFor(UI::USELESS_CHAR);
	ThankYouForPlayingLayer->CombineUiLines();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::shared_ptr<RenderingLayer> EpilogBackgroundLayer = std::make_shared<RenderingLayer>((int)EEndingCanvasLayer::EpilogueBackground, UI::USELESS_CHAR);
	EndiningCanvasLayerIdMap[EEndingCanvasLayer::EpilogueBackground] = EpilogBackgroundLayer->GetLayerId();

	EpilogBackgroundLayer->ClearLayerFor(UI::USELESS_CHAR);
	EpilogBackgroundLayer->CombineUiLines();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::shared_ptr<RenderingLayer> EpilogueTextLayer = std::make_shared<RenderingLayer>((int)EEndingCanvasLayer::EpilogueText, UI::USELESS_CHAR);
	EndiningCanvasLayerIdMap[EEndingCanvasLayer::EpilogueText] = EpilogueTextLayer->GetLayerId();

	EpilogueTextLayer->ClearLayerFor(UI::USELESS_CHAR);
	EpilogueTextLayer->CombineUiLines();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::shared_ptr<RenderingCanvas> EndingCanvas = std::make_shared<RenderingCanvas>();
	EndingCanvas->AddLayer(BackgroundLayer);
	EndingCanvas->AddLayer(BackgrundArtLayer);
	EndingCanvas->AddLayer(GameOverLayer);
	EndingCanvas->AddLayer(ThankYouForPlayingLayer);
	EndingCanvas->AddLayer(EpilogBackgroundLayer);
	EndingCanvas->AddLayer(EpilogueTextLayer);

	AddRenderingCanvas(ERenderingCanvas::Ending, EndingCanvas);
}

void UIManager::MakeInventorySceneUI()
{
	std::shared_ptr<RenderingLayer> BackgroundLayer = std::make_shared<RenderingLayer>((int)EInventoryCanvasLayer::Background);
	InventoryCanvasLayerIdMap[EInventoryCanvasLayer::Background] = BackgroundLayer->GetLayerId();

	BackgroundLayer->ClearLayerFor(L' ');
	BackgroundLayer->CombineUiLines();

	std::shared_ptr<RenderingLayer> ItemListLayer = std::make_shared<RenderingLayer>((int)EInventoryCanvasLayer::ItemList, UI::USELESS_CHAR);
	InventoryCanvasLayerIdMap[EInventoryCanvasLayer::ItemList] = ItemListLayer->GetLayerId();

	ItemListLayer->ClearLayerFor(UI::USELESS_CHAR);

	std::shared_ptr<RenderingCanvas> InventoryCanvas = std::make_shared<RenderingCanvas>();
	InventoryCanvas->AddLayer(BackgroundLayer);
	InventoryCanvas->AddLayer(ItemListLayer);

	AddRenderingCanvas(ERenderingCanvas::Inventory, InventoryCanvas);
}

void UIManager::AddMessageToBasicCanvasEventInfoUI(const std::wstring& NewMessage, bool bShouldUpdateUI)
{
	int EventInfoUIContentsLayerId = BasicCanvasLayerIdMap[EBasicCanvasLayer::EventInfoUIContents];

	std::shared_ptr<RenderingLayer> EventInfoUIContentsLayer = RenderingCanvasMap[ERenderingCanvas::Basic]->GetRenderingLayer(EventInfoUIContentsLayerId);
	if (EventInfoUIContentsLayer == nullptr)
	{
		std::cout << "UIManager, AddMessageToBasicCanvasEventInfoUI : Fail to get Layer" << std::endl;
		return;
	}

	int MsgSize = (int)NewMessage.size();
	int MsgActualLength = 0;
	for (int i = 0; i < MsgSize; ++i)
	{
		if (LogicHelper::IsHangul(NewMessage[i]) || LogicHelper::IsHanja(NewMessage[i]))
		{
			MsgActualLength += 2;
		}
		else
		{
			MsgActualLength++;
		}
	}

	int RemainSpace = UI::EVENT_INFO_UI_CONTENT_ACTUAL_MAX_LENGTH - MsgActualLength;

	std::wstring ModifiedMsg;
	ModifiedMsg.reserve(UI::EVENT_INFO_UI_CONTENT_ACTUAL_MAX_LENGTH);
	ModifiedMsg = NewMessage;


	for (int i = 0; i < RemainSpace; ++i)
	{
		ModifiedMsg.push_back(L' ');
	}

	EventInfoUIContentsMsgs.push_back(ModifiedMsg);

	if (EventInfoUIContentsMsgs.size() > UI::EVENT_INFO_UI_CONTENTS_COUNT)
	{
		EventInfoUIContentsMsgs.pop_front();
	}

	int i = 0;
	for (auto& Msg : EventInfoUIContentsMsgs)
	{
		EventInfoUIContentsLayer->DrawString(UI::EVENT_INFO_UI_CONTENTS_FIRST_POSITION_X + i, UI::EVENT_INFO_UI_CONTENTS_FIRST_POSITION_Y, Msg);
		i++;
	}

	EventInfoUIContentsLayer->CombineUiLines();
	
	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Basic);
	}
}

void UIManager::ClearMessageToBasicCanvasEventInfoUI(bool bShouldUpdateUI)
{
	int EventInfoUIContentsLayerId = BasicCanvasLayerIdMap[EBasicCanvasLayer::EventInfoUIContents];

	std::shared_ptr<RenderingLayer> EventInfoUIContentsLayer = RenderingCanvasMap[ERenderingCanvas::Basic]->GetRenderingLayer(EventInfoUIContentsLayerId);
	if (EventInfoUIContentsLayer == nullptr)
	{
		std::cout << "UIManager, AddMessageToBasicCanvasEventInfoUI : Fail to get Layer" << std::endl;
		return;
	}

	AddMessageToBasicCanvasEventInfoUI(L" ", false);
	AddMessageToBasicCanvasEventInfoUI(L" ", false);
	AddMessageToBasicCanvasEventInfoUI(L" ", false);
	AddMessageToBasicCanvasEventInfoUI(L" ", false);

	EventInfoUIContentsMsgs.resize(0);

	EventInfoUIContentsLayer->CombineUiLines();

	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Basic);
	}
}

void UIManager::ChangeBasicCanvasJobInfoUI(int JobChoice, bool bShouldUpdateUI)
{
	if (JobChoice < 1 || JobChoice > 3)
	{
		std::cout << "UIManager::ChangeBasicCanvasJobInfoUI, Weird JobChoice : " << JobChoice << std::endl;
		return;
	}

	std::wstring JobInfoString;
	JobInfoString.reserve(10);
	JobInfoString = L"직  업 ";

	switch (JobChoice)
	{
	case 1:

		JobInfoString += L"전사  ";
		break;

	case 2:
		JobInfoString += L"마법사";
		break;

	case 3:
		JobInfoString += L"도적  ";
		break;

	default:
		std::cout << "UIManager::ChangeBasicCanvasJobInfoUI, 잘못된 입력입니다." << std::endl;
	}

	int StatInfoLayerId = BasicCanvasLayerIdMap[EBasicCanvasLayer::StatInfo];

	std::shared_ptr<RenderingLayer> StatInfoLayer = RenderingCanvasMap[ERenderingCanvas::Basic]->GetRenderingLayer(StatInfoLayerId);
	if (StatInfoLayer == nullptr)
	{
		std::cout << "UIManager, ChangeBasicCanvasJobInfoUI : Fail to get Layer" << std::endl;
		return;
	}

	int PositionX = UI::STAT_INFO_UI_FIRST_POSITION_X;

	StatInfoLayer->DrawString(PositionX, UI::STAT_INFO_UI_FIRST_POSITION_Y - 2, JobInfoString);
	StatInfoLayer->CombineUiLines();
	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Basic);
	}
}

void UIManager::ChangeBasicCanvasLevelInfoUI(int Amount, bool bShouldUpdateUI)
{
	int StatInfoLayerId = BasicCanvasLayerIdMap[EBasicCanvasLayer::StatInfo];

	std::shared_ptr<RenderingLayer> StatInfoLayer = RenderingCanvasMap[ERenderingCanvas::Basic]->GetRenderingLayer(StatInfoLayerId);
	if (StatInfoLayer == nullptr)
	{
		std::cout << "UIManager, ChangeBasicCanvasStatInfoUI : Fail to get Layer" << std::endl;
		return;
	}

	int MaxLevelTextLength = 6;

	std::wstring StatInfoString;
	StatInfoString.reserve(MaxLevelTextLength);

	int PositionX = UI::STAT_INFO_UI_FIRST_POSITION_X + 1;
	StatInfoString = L"레  벨 ";

	std::wstring NumberString = std::to_wstring(Amount);

	StatInfoString += NumberString;

	int SpaceCount = MaxLevelTextLength - (int)NumberString.size();
	for (int i = 0; i < SpaceCount; ++i)
	{
		StatInfoString.push_back(L' ');
	}

	StatInfoLayer->DrawString(PositionX, UI::STAT_INFO_UI_FIRST_POSITION_Y - 2, StatInfoString);
	StatInfoLayer->CombineUiLines();
	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Basic);
	}
}

void UIManager::ChangeBasicCanvasExpInfoUI(int Amount, bool bShouldUpdateUI)
{
	int StatInfoLayerId = BasicCanvasLayerIdMap[EBasicCanvasLayer::StatInfo];

	std::shared_ptr<RenderingLayer> StatInfoLayer = RenderingCanvasMap[ERenderingCanvas::Basic]->GetRenderingLayer(StatInfoLayerId);
	if (StatInfoLayer == nullptr)
	{
		std::cout << "UIManager, ChangeBasicCanvasExpInfoUI : Fail to get Layer" << std::endl;
		return;
	}

	int MaxExpTextLength = 6;
	
	std::wstring StatInfoString;
	StatInfoString.reserve(MaxExpTextLength);

	int PositionX = UI::STAT_INFO_UI_FIRST_POSITION_X + 2;
	StatInfoString = L"경험치 ";

	std::wstring NumberString = std::to_wstring(Amount) + L'/' + std::to_wstring(MaxExpUIInfo);

	CurrentExpUIInfo = Amount;

	StatInfoString += NumberString;
	int SpaceCount = MaxExpTextLength - (int)NumberString.size();
	for (int i = 0; i < SpaceCount; ++i)
	{
		StatInfoString.push_back(L' ');
	}

	StatInfoLayer->DrawString(PositionX, UI::STAT_INFO_UI_FIRST_POSITION_Y - 2, StatInfoString);
	StatInfoLayer->CombineUiLines();
	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Basic);
	}
}

void UIManager::ChangeBasicCanvasMaxExpInfoUI(int Amount, bool bShouldUpdateUI)
{
	int StatInfoLayerId = BasicCanvasLayerIdMap[EBasicCanvasLayer::StatInfo];

	std::shared_ptr<RenderingLayer> StatInfoLayer = RenderingCanvasMap[ERenderingCanvas::Basic]->GetRenderingLayer(StatInfoLayerId);
	if (StatInfoLayer == nullptr)
	{
		std::cout << "UIManager, ChangeBasicCanvasMaxExpInfoUI : Fail to get Layer" << std::endl;
		return;
	}
	
	int MaxExpTextLength = 7;

	std::wstring StatInfoString;
	StatInfoString.reserve(MaxExpTextLength);

	int PositionX = UI::STAT_INFO_UI_FIRST_POSITION_X + 2;
	StatInfoString = L"경험치 ";

	std::wstring NumberString = std::to_wstring(CurrentExpUIInfo) + L'/' + std::to_wstring(Amount);

	MaxExpUIInfo = Amount;

	StatInfoString += NumberString;

	int SpaceCount = MaxExpTextLength - (int)NumberString.size();
	for (int i = 0; i < SpaceCount; ++i)
	{
		StatInfoString.push_back(L' ');
	}

	StatInfoLayer->DrawString(PositionX, UI::STAT_INFO_UI_FIRST_POSITION_Y - 2, StatInfoString);
	StatInfoLayer->CombineUiLines();
	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Basic);
	}
}

void UIManager::ChangeBasicCanvasMoneyInfoUI(int Amount, bool bShouldUpdateUI)
{
	int StatInfoLayerId = BasicCanvasLayerIdMap[EBasicCanvasLayer::StatInfo];

	std::shared_ptr<RenderingLayer> StatInfoLayer = RenderingCanvasMap[ERenderingCanvas::Basic]->GetRenderingLayer(StatInfoLayerId);
	if (StatInfoLayer == nullptr)
	{
		std::cout << "UIManager, ChangeBasicCanvasMoneyInfoUI : Fail to get Layer" << std::endl;
		return;
	}

	int MaxMoneyTextLength = 6;

	std::wstring StatInfoString;
	StatInfoString.reserve(MaxMoneyTextLength);

	int PositionX = UI::STAT_INFO_UI_FIRST_POSITION_X + 7;
	StatInfoString = L"소지금 ";

	std::wstring NumberString = std::to_wstring(Amount);

	StatInfoString += NumberString;

	int SpaceCount = MaxMoneyTextLength - (int)NumberString.size();
	for (int i = 0; i < SpaceCount; ++i)
	{
		StatInfoString.push_back(L' ');
	}

	StatInfoLayer->DrawString(PositionX, UI::STAT_INFO_UI_FIRST_POSITION_Y - 2, StatInfoString);
	StatInfoLayer->CombineUiLines();
	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Basic);
	}
}

void UIManager::ChangeBasicCanvasStatInfoUI(EStat StatType, int Amount, bool bShouldUpdateUI)
{
	int StatInfoLayerId = BasicCanvasLayerIdMap[EBasicCanvasLayer::StatInfo];

	std::shared_ptr<RenderingLayer> StatInfoLayer = RenderingCanvasMap[ERenderingCanvas::Basic]->GetRenderingLayer(StatInfoLayerId);
	if (StatInfoLayer == nullptr)
	{
		std::cout << "UIManager, ChangeBasicCanvasStatInfoUI : Fail to get Layer" << std::endl;
		return;
	}

	int MaxStatNumberTextLength = 7;

	std::wstring StatInfoString;
	StatInfoString.reserve(MaxStatNumberTextLength);

	int PositionX = UI::STAT_INFO_UI_FIRST_POSITION_X;
	int PositionY = UI::STAT_INFO_UI_FIRST_POSITION_Y - 2;
	
	if (StatType == EStat::CurHp || StatType == EStat::MaxHp)
	{
		StatInfoString = L"체  력 ";
		PositionX += 3;
	}
	else if (StatType == EStat::Power)
	{
		StatInfoString = L"공격력 ";
		PositionX += 4;
	}
	else if (StatType == EStat::Defense)
	{
		StatInfoString = L"방어력 ";
		PositionX += 5;
	}
	else if (StatType == EStat::Luck)
	{
		StatInfoString = L"행  운 ";
		PositionX += 6;
	}

	std::wstring NumberString = L"";

	if (StatType == EStat::CurHp)
	{
		CurrentHpUIInfo = Amount;
		NumberString = std::to_wstring(Amount) + L'/' + std::to_wstring(MaxHpUIInfo);
	}
	else if (StatType == EStat::MaxHp)
	{
		MaxHpUIInfo = Amount;
		NumberString = std::to_wstring(CurrentHpUIInfo) + L'/' + std::to_wstring(Amount);
	}
	else
	{
		NumberString = std::to_wstring(Amount);
	}

	StatInfoString += NumberString;

	int SpaceCount = MaxStatNumberTextLength - (int)NumberString.size();
	for(int i = 0; i < SpaceCount; ++i)
	{
		StatInfoString.push_back(L' ');
	}

	StatInfoLayer->DrawString(PositionX, PositionY, StatInfoString);
	StatInfoLayer->CombineUiLines();
	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Basic);
	}
}

void UIManager::ChangeBasicCanvasArtImage(const FASCIIArtContainer& ArtContainer, bool bShouldUpdateUI, int OffsetX, int OffsetY)
{
	int ArtLayerId = BasicCanvasLayerIdMap[EBasicCanvasLayer::Art];
	std::shared_ptr<RenderingLayer> ArtLayer = RenderingCanvasMap[ERenderingCanvas::Basic]->GetRenderingLayer(ArtLayerId);

	if (ArtLayer == nullptr)
	{
		std::cout << "UIManager, ChangeBasicCanvasArtImage : Fail to get Layer" << std::endl;
		return;
	}
	
	int CenterCoordX = (UI::EVENT_INFO_UI_BORDER_FIRST_POSITION_X - UI::BACKGRUOND_BORDER_FIRST_POSITION_X) / 2;
	int CenterCoordY = UI::BACKGROUND_BORDER_FIRST_POSITION_Y + UI::BACKGROUND_BORDER_WIDTH / 2;

	int ArtWidth = ArtContainer.GetWidth();
	int ArtHeight = ArtContainer.GetHeight();
	
	int DrawCoordX = CenterCoordX - ArtHeight / 2;
	int DrawCoordY = CenterCoordY - ArtWidth / 2;

	ArtLayer->ClearLayerFor(UI::USELESS_CHAR);
	ArtLayer->DrawSurface(DrawCoordX + OffsetX, DrawCoordY + OffsetY, ArtContainer.ArtLines);

	ArtLayer->CombineUiLines();

	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Basic);
	}
}

void UIManager::SetBasicCanvasLayerHide(bool bShouldHide, EBasicCanvasLayer LayerType, bool bShouldUpdateUI)
{
	int LayerId = BasicCanvasLayerIdMap[LayerType];
	std::shared_ptr<RenderingLayer> Layer = RenderingCanvasMap[ERenderingCanvas::Basic]->GetRenderingLayer(LayerId);

	if (Layer == nullptr)
	{
		std::cout << "UIManager, SetBasicCanvasLayerHide : Fail to get Layer" << std::endl;
		return;
	}

	Layer->SetIsHiding(bShouldHide);

	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Basic);
	}
}

void UIManager::SetBasicCanvasMonsterInfoUI(const std::string& MonsterName, int MonsterHp, bool bShouldUpdateUI)
{
	int LayerId = BasicCanvasLayerIdMap[EBasicCanvasLayer::MonsterInfo];
	std::shared_ptr<RenderingLayer> Layer = RenderingCanvasMap[ERenderingCanvas::Basic]->GetRenderingLayer(LayerId);

	if (Layer == nullptr)
	{
		std::cout << "UIManager, SetBasicCanvasMonsterInfoUI : Fail to get Layer" << std::endl;
		return;
	}

	std::string MonsterHpString = to_string(MonsterHp);
	std::wstring NameWString = LogicHelper::StringToWString(MonsterName);
	std::wstring HpWString = L"HP : " + LogicHelper::StringToWString(MonsterHpString);

	int PositionX = UI::BACKGRUOND_BORDER_FIRST_POSITION_X + 2;
	int PositionY = UI::BACKGROUND_BORDER_FIRST_POSITION_Y + UI::BACKGROUND_BORDER_WIDTH / 2;

	Layer->DrawString(PositionX, PositionY - (int)NameWString.size() / 2, L"                        ");
	Layer->DrawString(PositionX + 1, PositionY - (int)HpWString.size() / 2, L"                   ");
	Layer->DrawString(PositionX, PositionY - (int)NameWString.size() / 2, NameWString);
	Layer->DrawString(PositionX + 1, PositionY - (int)HpWString.size() / 2, HpWString);

	Layer->CombineUiLines();

	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Basic);
	}
}

void UIManager::SetOpeningCanvasTitleArt(int PositionX, int PositionY, const FASCIIArtContainer& ArtContainer, bool bShouldUpdateUI)
{
	int TitleLayerId = OpeningCanvasLayerIdMap[EOpeningCanvasLayer::Title];
	std::shared_ptr<RenderingLayer> TitleLayer = RenderingCanvasMap[ERenderingCanvas::Opening]->GetRenderingLayer(TitleLayerId);

	if (TitleLayer == nullptr)
	{
		std::cout << "UIManager, ChangeBasicCanvasArtImage : Fail to get Layer" << std::endl;
		return;
	}

	TitleLayer->ClearLayerFor(UI::USELESS_CHAR);

	TitleLayer->DrawSurface(PositionX, PositionY, ArtContainer.ArtLines);

	TitleLayer->CombineUiLines();

	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Opening);
	}
}

void UIManager::SetOpeningCanvasBackgroundArt(int PositionX, int PositionY, const std::vector<std::wstring>& Surface, bool bShouldUpdateUI)
{
	int TitleLayerId = OpeningCanvasLayerIdMap[EOpeningCanvasLayer::BackgroundArt];
	std::shared_ptr<RenderingLayer> TitleLayer = RenderingCanvasMap[ERenderingCanvas::Opening]->GetRenderingLayer(TitleLayerId);

	if (TitleLayer == nullptr)
	{
		std::cout << "UIManager, ChangeBasicCanvasArtImage : Fail to get Layer" << std::endl;
		return;
	}

	TitleLayer->ClearLayerFor(L' ');
	TitleLayer->DrawSurface(PositionX, PositionY, Surface);

	TitleLayer->CombineUiLines();

	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Opening);
	}
}

void UIManager::SetOpeningCanvasLayerHide(bool bShouldHide, EOpeningCanvasLayer LayerType, bool bShouldUpdateUI)
{
	int LayerId = OpeningCanvasLayerIdMap[LayerType];
	std::shared_ptr<RenderingLayer> Layer = RenderingCanvasMap[ERenderingCanvas::Opening]->GetRenderingLayer(LayerId);

	if (Layer == nullptr)
	{
		std::cout << "UIManager, SetOpeningCanvasLayerHide : Fail to get Layer" << std::endl;
		return;
	}

	Layer->SetIsHiding(bShouldHide);

	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Opening);
	}
}

void UIManager::SetOpeningCanvasPrologueBackgroundArt(const FASCIIArtContainer& ArtContainer, bool bShouldUpdateUI, int OffsetX, int OffsetY)
{
	int LayerId = OpeningCanvasLayerIdMap[EOpeningCanvasLayer::PrologBackground];
	std::shared_ptr<RenderingLayer> Layer = RenderingCanvasMap[ERenderingCanvas::Opening]->GetRenderingLayer(LayerId);

	if (Layer == nullptr)
	{
		std::cout << "UIManager, SetOpeningCanvasPrologueBackgroundArt : Fail to get Layer" << std::endl;
		return;
	}

	int CenterCoordX = UI::CENTER_OF_UI_X;
	int CenterCoordY = UI::CENTER_OF_UI_Y;

	int ArtWidth = ArtContainer.GetWidth();
	int ArtHeight = ArtContainer.GetHeight();

	int DrawCoordX = CenterCoordX - ArtHeight / 2;
	int DrawCoordY = CenterCoordY - ArtWidth / 2;

	//InventoryLayer->ClearLayerFor(UI::USELESS_CHAR);

	Layer->DrawSurface(DrawCoordX + OffsetX, DrawCoordY + OffsetY, ArtContainer.ArtLines);
	Layer->CombineUiLines();

	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Opening);
	}
}

void UIManager::SetOpeningCanvasPrologueText(const FStoryTextContainer& StoryTextConatiner, int PositionX, int PositionY, bool bShouldUpdateUI)
{
	const std::vector<std::wstring>& StoryTextLines = StoryTextConatiner.StoryTextLines;
	int StoryTextCount = (int)StoryTextLines.size();

	if (StoryTextLines.size() <= 0)
	{
		std::cout << "UIManager, SetOpeningCanvasPrologueText : StoryTextConatiner.StoryTextLines.size() <= 0" << std::endl;
		return;
	}

	int LayerId = OpeningCanvasLayerIdMap[EOpeningCanvasLayer::PrologueText];
	std::shared_ptr<RenderingLayer> Layer = RenderingCanvasMap[ERenderingCanvas::Opening]->GetRenderingLayer(LayerId);

	if (Layer == nullptr)
	{
		std::cout << "UIManager, SetOpeningCanvasPrologueText : Fail to get Layer" << std::endl;
		return;
	}

	const int ArtHeight = 20;
	const int ArtWidth = 80;

	const int NewPositionX = PositionX + UI::CENTER_OF_UI_X - StoryTextCount / 2;
	const int NewPositionY = PositionY + UI::CENTER_OF_UI_Y - ArtWidth / 2;

	for (int i = 0; i < StoryTextCount; ++i)
	{
		std::wstring NewStoryText = L"";

		int StoryTextSize = (int)StoryTextLines[i].size();
		int HangeulCount = 0;

		for (int j = 0; j < StoryTextSize; ++j)
		{
			if (LogicHelper::IsHangul(StoryTextLines[i][j]))
			{
				HangeulCount++;
			}
		}

		int NeededEmptySpaceCount = ArtWidth - StoryTextSize - HangeulCount;
		
		for (int j = 0; j < NeededEmptySpaceCount / 2; ++j)
		{
			NewStoryText += L' ';
		}

		NewStoryText += StoryTextLines[i];

		for (int j = 0; j < NeededEmptySpaceCount / 2; ++j)
		{
			NewStoryText += L' ';
		}

		Layer->DrawString(NewPositionX + i, NewPositionY, NewStoryText);
	}

	Layer->CombineUiLines();

	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Opening);
	}
}

void UIManager::DrawOpeningCanvasPrologue(const FStoryTextContainer& StoryTextConatiner, bool bShouldUpdateUI, int OffsetX, int OffsetY)
{
	const FASCIIArtContainer& ArtContainer = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Test);
	SetOpeningCanvasPrologueBackgroundArt(ArtContainer, false, OffsetX, OffsetY);
	SetOpeningCanvasPrologueText(StoryTextConatiner, OffsetX, OffsetY, bShouldUpdateUI);
}

void UIManager::SetInventoryCanvasBackgroundImage(const FASCIIArtContainer& ArtContainer, bool bShouldUpdateUI, int OffsetX, int OffsetY)
{
	int LayerId = InventoryCanvasLayerIdMap[EInventoryCanvasLayer::Background];
	std::shared_ptr<RenderingLayer> InventoryLayer = RenderingCanvasMap[ERenderingCanvas::Inventory]->GetRenderingLayer(LayerId);

	if (InventoryLayer == nullptr)
	{
		std::cout << "UIManager, SetInventoryCanvasBackgroundImage : Fail to get Layer" << std::endl;
		return;
	}

	InventoryLayer->DrawSurface(UI::INVENTORY_BACKGROUND_FIRST_POSITION_X + OffsetX, UI::INVENTORY_BACKGROUND_FIRST_POSITION_Y + OffsetY, ArtContainer.ArtLines);
	InventoryLayer->CombineUiLines();

	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Inventory);
	}
}

void UIManager::SetInventoryCanvasItemList(const std::vector<std::shared_ptr<IItem>>& InventoryInfo, int PositionX, int PositionY, bool bShouldUpdateUI)
{
	int LayerId = InventoryCanvasLayerIdMap[EInventoryCanvasLayer::ItemList];
	std::shared_ptr<RenderingLayer> InventoryLayer = RenderingCanvasMap[ERenderingCanvas::Inventory]->GetRenderingLayer(LayerId);

	if (InventoryLayer == nullptr)
	{
		std::cout << "UIManager, SetInventoryCanvasItemList : Fail to get Layer" << std::endl;
		return;
	}

	std::wstring ItemInfoText = L"";

	int MaxDisplayableItemCount = 10;

	int ItemCount = std::min(MaxDisplayableItemCount, (int)InventoryInfo.size());
	InventoryLayer->ClearLayerFor(UI::USELESS_CHAR);

	for (int i = 0; i < ItemCount; ++i)
	{
		std::wstring WItemName = LogicHelper::StringToWString(InventoryInfo[i]->GetName());
		std::wstring WItemDescription = LogicHelper::StringToWString(InventoryInfo[i]->GetExplanation());

		ItemInfoText = std::to_wstring(i + 1) + L". " + WItemName + L" : " + WItemDescription;
		InventoryLayer->DrawString(PositionX + i * 2, PositionY, ItemInfoText);
	}

	for (int i = ItemCount; i < MaxDisplayableItemCount; ++i)
	{
		std::wstring EmptySpaceText = std::to_wstring(i + 1) + L".                                              ";
		InventoryLayer->DrawString(PositionX + i * 2, PositionY, EmptySpaceText);
	}

	InventoryLayer->CombineUiLines();

	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Inventory);
	}
}

void UIManager::DrawInventory(const std::vector<std::shared_ptr<IItem>>& InventoryInfo, bool bShouldUpdateUI, int OffsetX, int OffsetY)
{
	const FASCIIArtContainer& ArtContainer = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Test);
	
	int CenterCoordX = UI::CENTER_OF_UI_X;
	int CenterCoordY = UI::CENTER_OF_UI_Y;

	int ArtWidth = ArtContainer.GetWidth();
	int ArtHeight = ArtContainer.GetHeight();

	int DrawCoordX = CenterCoordX - ArtHeight / 2 + 9;
	int DrawCoordY = CenterCoordY - ArtWidth / 2 + 15;

	SetInventoryCanvasItemList(InventoryInfo, DrawCoordX + OffsetX, DrawCoordY + OffsetY, false);
	SetInventoryCanvasBackgroundImage(ArtContainer, bShouldUpdateUI, OffsetX, OffsetY + 10);
}

void UIManager::OpenInventory()
{
	// 구현 예정

	DrawInventory(Character::GetInstance().GetInventory());

	EKey Key = EKey::UnAvailable;

	while (Key != EKey::i)
	{
		Key = InputReceiver::ChatchInput();
	}

}

void UIManager::SetEndingCanvasLayerHide(bool bShouldHide, EEndingCanvasLayer LayerType, bool bShouldUpdateUI)
{
	int LayerId = EndiningCanvasLayerIdMap[LayerType];
	std::shared_ptr<RenderingLayer> Layer = RenderingCanvasMap[ERenderingCanvas::Ending]->GetRenderingLayer(LayerId);

	if (Layer == nullptr)
	{
		std::cout << "UIManager, SetEndingCanvasLayerHide : Fail to get Layer" << std::endl;
		return;
	}

	Layer->SetIsHiding(bShouldHide);

	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Ending);
	}
}

void UIManager::SetEndingCanvasEpilogueBackground(const FASCIIArtContainer& ArtContainer, bool bShouldUpdateUI, int OffsetX, int OffsetY)
{
	int LayerId = EndiningCanvasLayerIdMap[EEndingCanvasLayer::EpilogueBackground];
	std::shared_ptr<RenderingLayer> Layer = RenderingCanvasMap[ERenderingCanvas::Ending]->GetRenderingLayer(LayerId);

	if (Layer == nullptr)
	{
		std::cout << "UIManager, SetEndingCanvasEpilogueBackground : Fail to get Layer" << std::endl;
		return;
	}

	int CenterCoordX = UI::CENTER_OF_UI_X;
	int CenterCoordY = UI::CENTER_OF_UI_Y;

	int ArtWidth = ArtContainer.GetWidth();
	int ArtHeight = ArtContainer.GetHeight();

	int DrawCoordX = CenterCoordX - ArtHeight / 2;
	int DrawCoordY = CenterCoordY - ArtWidth / 2;

	Layer->DrawSurface(DrawCoordX + OffsetX, DrawCoordY + OffsetY, ArtContainer.ArtLines);
	Layer->CombineUiLines();

	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Ending);
	}
}

void UIManager::SetEndingCanvasEpilogueText(const FStoryTextContainer& StoryTextConatiner, int PositionX, int PositionY, bool bShouldUpdateUI)
{
	const std::vector<std::wstring>& StoryTextLines = StoryTextConatiner.StoryTextLines;
	int StoryTextCount = (int)StoryTextLines.size();

	if (StoryTextLines.size() <= 0)
	{
		std::cout << "UIManager, SetEndingCanvasEpilogueText : StoryTextConatiner.StoryTextLines.size() <= 0" << std::endl;
		return;
	}

	int LayerId = EndiningCanvasLayerIdMap[EEndingCanvasLayer::EpilogueText];
	std::shared_ptr<RenderingLayer> Layer = RenderingCanvasMap[ERenderingCanvas::Ending]->GetRenderingLayer(LayerId);

	if (Layer == nullptr)
	{
		std::cout << "UIManager, SetEndingCanvasEpilogueText : Fail to get Layer" << std::endl;
		return;
	}

	const int ArtHeight = 20;
	const int ArtWidth = 80;

	const int NewPositionX = PositionX + UI::CENTER_OF_UI_X - StoryTextCount / 2;
	const int NewPositionY = PositionY + UI::CENTER_OF_UI_Y - ArtWidth / 2;

	for (int i = 0; i < StoryTextCount; ++i)
	{
		std::wstring NewStoryText = L"";

		int StoryTextSize = (int)StoryTextLines[i].size();
		int HangeulCount = 0;

		for (int j = 0; j < StoryTextSize; ++j)
		{
			if (LogicHelper::IsHangul(StoryTextLines[i][j]))
			{
				HangeulCount++;
			}
		}

		int NeededEmptySpaceCount = ArtWidth - StoryTextSize - HangeulCount;

		for (int j = 0; j < NeededEmptySpaceCount / 2; ++j)
		{
			NewStoryText += L' ';
		}

		NewStoryText += StoryTextLines[i];

		for (int j = 0; j < NeededEmptySpaceCount / 2; ++j)
		{
			NewStoryText += L' ';
		}

		Layer->DrawString(NewPositionX + i, NewPositionY, NewStoryText);
	}

	Layer->CombineUiLines();

	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Ending);
	}
}

void UIManager::DrawEndingCanvasPrologue(const FStoryTextContainer& StoryTextConatiner, bool bShouldUpdateUI, int OffsetX, int OffsetY)
{
	const FASCIIArtContainer& ArtContainer = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Test);
	SetEndingCanvasEpilogueBackground(ArtContainer, false, OffsetX, OffsetY);
	SetEndingCanvasEpilogueText(StoryTextConatiner, OffsetX, OffsetY, bShouldUpdateUI);
}

void UIManager::ShowGameOverScene()
{
	int LayerId = EndiningCanvasLayerIdMap[EEndingCanvasLayer::GameOver];
	std::shared_ptr<RenderingLayer> GameOverLayer = RenderingCanvasMap[ERenderingCanvas::Ending]->GetRenderingLayer(LayerId);

	if (GameOverLayer == nullptr)
	{
		std::cout << "UIManager, ShowGameOverScene : Fail to get Layer : GameOverLayer" << std::endl;
		return;
	}

	SetEndingCanvasLayerHide(true, EEndingCanvasLayer::BackgroundArt, false);
	SetEndingCanvasLayerHide(true, EEndingCanvasLayer::EpilogueBackground, false);
	SetEndingCanvasLayerHide(true, EEndingCanvasLayer::EpilogueText, false);
	SetEndingCanvasLayerHide(true, EEndingCanvasLayer::ThankYouForPlaying, false);
	SetEndingCanvasLayerHide(false, EEndingCanvasLayer::GameOver);

	Sleep(1000);

	/*int PositionX = UI::CENTER_OF_UI_X + 15;
	int PositionY = UI::CENTER_OF_UI_Y;

	GameOverLayer->DrawString(PositionX, PositionY, L"Press Enter Key To Continue");
	PrintUI(ERenderingCanvas::Ending);

	Sleep(10000);*/
}

void UIManager::SetConsoleColor(EUIColor UIColor)
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(ConsoleHandle, (WORD)UIColor);
}

void UIManager::BindAllDelegate()
{
	Character::GetInstance().OnCharacterChanged = [this](ECharacterEvent CharacterEvent, int Amount)
		{
			OnCharacterChanged(CharacterEvent, Amount);
		};

	Character::GetInstance().GetStatus().OnStatChanged = [this](EStat StatType, int Amount)
		{
			OnStatChanged(StatType, Amount);
		};

	TimerManager::GetInstance().OnTickForUIDelegate = [this](double Delta)
		{
			Tick(Delta);
		};

	GameManager::GetInstance().GetTileMap()->OnMapChanged = [this](const std::vector<std::vector<ETile>>& TileTypeInfos)
		{
			OnMinimapUIContentsChanged(TileTypeInfos);
		};
}

void UIManager::SetMinimapUIContents(/*std::vector<std::vector<ETile>> TileTypeInfos*/)
{
}

void UIManager::Tick(double DeltaTime)
{

}

void UIManager::OnMinimapUIContentsChanged(const std::vector<std::vector<ETile>>& TileTypeInfos)
{
	int MapSizeX = (int)TileTypeInfos.size();

	if (MapSizeX <= 0)
	{
		std::cout << "UIManager, OnMinimapUIContentsChanged : MapSizeX <= 0" << std::endl;
		return;
	}

	int MapSizeY = (int)TileTypeInfos[0].size();

	if (MapSizeY <= 0)
	{
		std::cout << "UIManager, OnMinimapUIContentsChanged : MapSizeY <= 0" << std::endl;
		return;
	}

	int MinimapContentsLayerId = BasicCanvasLayerIdMap[EBasicCanvasLayer::MinimapContents];

	std::shared_ptr<RenderingLayer> MinimapContentsLayer = RenderingCanvasMap[ERenderingCanvas::Basic]->GetRenderingLayer(MinimapContentsLayerId);
	if (MinimapContentsLayer == nullptr)
	{
		std::cout << "UIManager, OnMinimapUIContentsChanged : Fail to get Layer" << std::endl;
		return;
	}

	int StartCoordX = UI::MIMIMAP_BORDER_UI_FIRST_POSITION_X + 1;
	int StartCoordY = UI::MIMIMAP_BORDER_UI_FIRST_POSITION_Y + 2;

	MinimapUIContents.resize(MapSizeX, std::vector<wchar_t>());

	for (int i = 0; i < MapSizeX; ++i)
	{
		MinimapUIContents[i].resize(MapSizeY, L'O');

		for (int j = 0; j < MapSizeY; ++j)
		{
			wchar_t TileImage;

			if (TileTypeInfos[i][j] == ETile::Block)
			{
				TileImage = L'#';
			}
			else if (TileTypeInfos[i][j] == ETile::Blank)
			{
				TileImage = L'.';
			}
			else if (TileTypeInfos[i][j] == ETile::Character)
			{
				TileImage = L'X';
			}
			else if (TileTypeInfos[i][j] == ETile::DemonLordCastle)
			{
				TileImage = L'?';
			}
			else if (TileTypeInfos[i][j] == ETile::Village1 ||
				TileTypeInfos[i][j] == ETile::Village2 ||
				TileTypeInfos[i][j] == ETile::Village2_Disabled)
			{
				TileImage = L'V';
			}
			else
			{
				std::cout << "UIManager, OnMinimapUIContentsChanged : Weird Tile Type" << std::endl;
				return;
			}

			if (MinimapUIContents[i][j] == TileImage)
			{
				continue;
			}

			MinimapUIContents[i][j] = TileImage;
			MinimapContentsLayer->DrawWCharacter(StartCoordX + i, StartCoordY + j, TileImage);
		}
	}

	MinimapContentsLayer->CombineUiLines();

	int MinimapBorderLayerId = BasicCanvasLayerIdMap[EBasicCanvasLayer::MinimapBorder];

	std::shared_ptr<RenderingLayer> MinimapBorderLayer = RenderingCanvasMap[ERenderingCanvas::Basic]->GetRenderingLayer(MinimapBorderLayerId);
	if (MinimapBorderLayer == nullptr)
	{
		std::cout << "UIManager, OnMinimapUIContentsChanged : Fail to get Layer" << std::endl;
		return;
	}

	MinimapBorderLayer->DrawRectanlge(UI::MIMIMAP_BORDER_UI_FIRST_POSITION_X, UI::MIMIMAP_BORDER_UI_FIRST_POSITION_Y, MapSizeY + 3, MapSizeX + 2);
	MinimapBorderLayer->CombineUiLines();
}

void UIManager::OnCharacterChanged(ECharacterEvent CharacterEvent, int Amount)
{
	//직업, 레벨 경험치 체력 공격력 방어력 행운 돈

	switch (CharacterEvent)
	{
	case ECharacterEvent::Level:
		ChangeBasicCanvasLevelInfoUI(Amount, false);
		break;
	case ECharacterEvent::Exp:
		ChangeBasicCanvasExpInfoUI(Amount, false);
		break;
	case ECharacterEvent::Job:
		ChangeBasicCanvasJobInfoUI(Amount, false);
		break;
	case ECharacterEvent::Gold:
		ChangeBasicCanvasMoneyInfoUI(Amount, false);
		break;
	case ECharacterEvent::MaxExp:
		ChangeBasicCanvasMaxExpInfoUI(Amount, false);
		break;
	default:
		break;
	}
}

void UIManager::OnStatChanged(EStat StatType, int Amount)
{
	ChangeBasicCanvasStatInfoUI(StatType, Amount, false);
}

UIManager::~UIManager()
{
}


