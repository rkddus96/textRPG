#include "UIManager.h"
#include "../RenderingCanvas.h"
#include "../LogicHelper.h"
#include "../RenderingLayer.h"
#include "../ConstantContainer.h"
#include "GameManager.h"
#include "TimerManager.h"
#include <functional>
#include "../Character.h"
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

void UIManager::OnStatChanged(EStat StatType, int Amount)
{
	std::wstring Text = L"";
	switch (StatType)
	{
	case EStat::MaxHp:
		Text += L"MaxHp Changed to : " + std::to_wstring(Amount);
		break;
	case EStat::CurHp:
		Text += L"CurHp Changed to : " + std::to_wstring(Amount);
		break;
	case EStat::Power:
		Text += L"Power Changed to : " + std::to_wstring(Amount);
		break;
	case EStat::Luck:
		Text += L"Luck Changed to : " + std::to_wstring(Amount);
		break;
	case EStat::Defense:
		Text += L"Defense Changed to : " + std::to_wstring(Amount);
		break;
	default:
		break;
	}

	LogicHelper::PrintWStringFast(Text);
}

void UIManager::Init()
{
	MakeEmtpyCanvasUI();
	MakeOpningSceneUI();

	int PredictedMinimapWidth = 10;
	int PredictedMinimapHeight = 10;
	MinimapUIContents = std::vector<std::vector<wchar_t>>(PredictedMinimapHeight, std::vector<wchar_t>(PredictedMinimapWidth, L'O'));
	MakeBasicUI();
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

	MiniMapContentsLayer->ClearLayerFor(L' ');

	std::shared_ptr<RenderingLayer> ArtLayer = std::make_shared<RenderingLayer>((int)EBasicCanvasLayer::Art, UI::USELESS_CHAR);
	BasicCanvasLayerIdMap[EBasicCanvasLayer::Art] = ArtLayer->GetLayerId();

	std::shared_ptr<RenderingLayer> VfxLayer = std::make_shared<RenderingLayer>((int)EBasicCanvasLayer::Vfx);
	BasicCanvasLayerIdMap[EBasicCanvasLayer::Vfx] = VfxLayer->GetLayerId();

	std::shared_ptr<RenderingLayer> BackgroundBorderLayer = std::make_shared<RenderingLayer>((int)EBasicCanvasLayer::BackgroundBorder);
	BasicCanvasLayerIdMap[EBasicCanvasLayer::BackgroundBorder] = BackgroundBorderLayer->GetLayerId();

	BackgroundBorderLayer->DrawRectanlge(1, 0, 218, 57);
	BackgroundBorderLayer->CombineUiLines();

	std::shared_ptr<RenderingLayer> MinimapBorderLayer = std::make_shared<RenderingLayer>((int)EBasicCanvasLayer::MinimapBorder);
	BasicCanvasLayerIdMap[EBasicCanvasLayer::MinimapBorder] = MinimapBorderLayer->GetLayerId();

	std::shared_ptr<RenderingLayer> EventInfoUIBorderLayer = std::make_shared<RenderingLayer>((int)EBasicCanvasLayer::EventInfoUIBorder);
	BasicCanvasLayerIdMap[EBasicCanvasLayer::EventInfoUIBorder] = EventInfoUIBorderLayer->GetLayerId();

	EventInfoUIBorderLayer->DrawRectanlge(51, 2, 214, 6);
	EventInfoUIBorderLayer->CombineUiLines();

	std::shared_ptr<RenderingLayer> EventInfoUIContentsLayer = std::make_shared<RenderingLayer>((int)EBasicCanvasLayer::EventInfoUIContents, UI::USELESS_CHAR);
	BasicCanvasLayerIdMap[EBasicCanvasLayer::EventInfoUIContents] = EventInfoUIContentsLayer->GetLayerId();

	EventInfoUIContentsLayer->ClearLayerFor(UI::USELESS_CHAR); // 한글 쓰려면 Layer의 마스크랑 같은 문자로 Clear를 한 번 해줘야 한다........

	std::shared_ptr<RenderingLayer> StatInfoLayer = std::make_shared<RenderingLayer>((int)EBasicCanvasLayer::StatInfo, UI::USELESS_CHAR);
	BasicCanvasLayerIdMap[EBasicCanvasLayer::StatInfo] = StatInfoLayer->GetLayerId();

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
	std::shared_ptr<RenderingLayer> BackgroundArtLayer = std::make_shared<RenderingLayer>((int)EOpeningCanvasLayer::BackgroundArt);
	OpeningCanvasLayerIdMap[EOpeningCanvasLayer::BackgroundArt] = BackgroundArtLayer->GetLayerId();

	BackgroundArtLayer->ClearLayerFor(L' ');
	BackgroundArtLayer-> CombineUiLines();

	std::shared_ptr<RenderingLayer> TitleLayer = std::make_shared<RenderingLayer>((int)EOpeningCanvasLayer::Title, UI::USELESS_CHAR);
	OpeningCanvasLayerIdMap[EOpeningCanvasLayer::Title] = TitleLayer->GetLayerId();

	std::shared_ptr<RenderingLayer> BackgroundBorderLayer = std::make_shared<RenderingLayer>((int)EOpeningCanvasLayer::BackgroundBorder);
	OpeningCanvasLayerIdMap[EOpeningCanvasLayer::BackgroundBorder] = BackgroundBorderLayer->GetLayerId();

	BackgroundBorderLayer->DrawRectanlge(1, 0, 218, 57);
	BackgroundBorderLayer->CombineUiLines();

	std::shared_ptr<RenderingLayer> PressEnterKeyToStartLayer = std::make_shared<RenderingLayer>((int)EOpeningCanvasLayer::PressEnterKeyToStart, UI::USELESS_CHAR);
	OpeningCanvasLayerIdMap[EOpeningCanvasLayer::PressEnterKeyToStart] = PressEnterKeyToStartLayer->GetLayerId();

	PressEnterKeyToStartLayer->ClearLayerFor(UI::USELESS_CHAR);
	PressEnterKeyToStartLayer->DrawString(40, 84, L"Press Enter Key To Start Game");
	PressEnterKeyToStartLayer->CombineUiLines();

	std::shared_ptr<RenderingCanvas> OpeningCanvas = std::make_shared<RenderingCanvas>();
	OpeningCanvas->AddLayer(BackgroundArtLayer);
	OpeningCanvas->AddLayer(TitleLayer);
	OpeningCanvas->AddLayer(BackgroundBorderLayer);
	OpeningCanvas->AddLayer(PressEnterKeyToStartLayer);

	AddRenderingCanvas(ERenderingCanvas::Opening, OpeningCanvas);
}

void UIManager::AddMessageToBasicCanvasEventInfoUI(const std::wstring& NewMessage)
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
}

void UIManager::ChangeBasicCanvasStatInfoUI(ETempStatType StatType, int Amount)
{
	int StatInfoLayerId = BasicCanvasLayerIdMap[EBasicCanvasLayer::StatInfo];

	std::shared_ptr<RenderingLayer> StatInfoLayer = RenderingCanvasMap[ERenderingCanvas::Basic]->GetRenderingLayer(StatInfoLayerId);
	if (StatInfoLayer == nullptr)
	{
		std::cout << "UIManager, ChangeBasicCanvasStatInfoUI : Fail to get Layer" << std::endl;
		return;
	}

	int MaxLevelTextLength = 3;

	std::wstring StatInfoString;
	StatInfoString.reserve(MaxLevelTextLength);

	int PositionX = UI::STAT_INFO_UI_FIRST_POSITION_X;
	if (StatType == ETempStatType::Level)
	{
		StatInfoString = L"레  벨 ";
	}
	else if (StatType == ETempStatType::Hp)
	{
		StatInfoString = L"체  력 ";
		PositionX += 1;
	}
	else if (StatType == ETempStatType::Defence)
	{
		StatInfoString = L"방어력 ";
		PositionX += 2;
	}
	else if (StatType == ETempStatType::Power)
	{
		StatInfoString = L"공격력 ";
		PositionX += 3;
	}
	else if (StatType == ETempStatType::Luck)
	{
		StatInfoString = L"행  운 ";
		PositionX += 4;
	}
	else
	{
		std::cout << "UIManager, ChangeBasicCanvasStatInfoUI : Weird Stat Type" << std::endl;
		return;
	}

	std::wstring NumberString = std::to_wstring(Amount);

	int SpaceCount = MaxLevelTextLength - (int)NumberString.size();
	for(int i = 0; i < SpaceCount; ++i)
	{
		StatInfoString.push_back(L'0');
	}

	StatInfoString += NumberString;

	StatInfoLayer->DrawString(PositionX, UI::STAT_INFO_UI_FIRST_POSITION_Y, StatInfoString);
	StatInfoLayer->CombineUiLines();
}

void UIManager::ChangeBasicCanvasArtImage(const std::vector<std::wstring>& Surface)
{
	int ArtLayerId = BasicCanvasLayerIdMap[EBasicCanvasLayer::Art];
	std::shared_ptr<RenderingLayer> ArtLayer = RenderingCanvasMap[ERenderingCanvas::Basic]->GetRenderingLayer(ArtLayerId);

	if (ArtLayer == nullptr)
	{
		std::cout << "UIManager, ChangeBasicCanvasArtImage : Fail to get Layer" << std::endl;
		return;
	}

	ArtLayer->ClearLayerFor(UI::USELESS_CHAR);
	ArtLayer->DrawSurface(10, 15, Surface);

	ArtLayer->CombineUiLines();
}

void UIManager::SetBasicCanvasLayerHide(bool bShouldHide, EBasicCanvasLayer LayerType)
{
	int LayerId = BasicCanvasLayerIdMap[LayerType];
	std::shared_ptr<RenderingLayer> Layer = RenderingCanvasMap[ERenderingCanvas::Basic]->GetRenderingLayer(LayerId);

	if (Layer == nullptr)
	{
		std::cout << "UIManager, SetBasicCanvasLayerHide : Fail to get Layer" << std::endl;
		return;
	}

	Layer->SetIsHiding(bShouldHide);
}

void UIManager::SetOpeningCanvasTitleArt(int PositionX, int PositionY, const std::vector<std::wstring>& Surface)
{
	int TitleLayerId = OpeningCanvasLayerIdMap[EOpeningCanvasLayer::Title];
	std::shared_ptr<RenderingLayer> TitleLayer = RenderingCanvasMap[ERenderingCanvas::Opening]->GetRenderingLayer(TitleLayerId);

	if (TitleLayer == nullptr)
	{
		std::cout << "UIManager, ChangeBasicCanvasArtImage : Fail to get Layer" << std::endl;
		return;
	}

	TitleLayer->ClearLayerFor(UI::USELESS_CHAR);
	TitleLayer->DrawSurface(PositionX, PositionY, Surface);

	TitleLayer->CombineUiLines();
}

void UIManager::SetOpeningCanvasLayerHide(bool bShouldHide, EOpeningCanvasLayer LayerType)
{
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
}

void UIManager::SetMinimapUIContents()
{
	// TODO : 맵 타일 내용 받아서 그리기
}

void UIManager::Tick(double DeltaTime)
{

}

void UIManager::OnMinimapUIContentsChanged(const std::vector<std::vector<ETempTileType>>& TileTypeInfos)
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

			if (TileTypeInfos[i][j] == ETempTileType::Block)
			{
				TileImage = L' ';
			}
			else if (TileTypeInfos[i][j] == ETempTileType::Blank)
			{
				TileImage = L'O';
			}
			else if (TileTypeInfos[i][j] == ETempTileType::Character)
			{
				TileImage = L'X';
			}
			else if (TileTypeInfos[i][j] == ETempTileType::DemonLordCastle)
			{
				TileImage = L'?';
			}
			else if (TileTypeInfos[i][j] == ETempTileType::Village1 ||
				TileTypeInfos[i][j] == ETempTileType::Village2 ||
				TileTypeInfos[i][j] == ETempTileType::Village2_Disabled)
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
	if (CharacterEvent == ECharacterEvent::Exp)
	{
		std::wstring test = L"Exp : " + std::to_wstring(Amount);

		LogicHelper::PrintWStringFast(test);
	}
	else if (CharacterEvent == ECharacterEvent::Level)
	{
		std::wstring test = L"Level : " + std::to_wstring(Amount);

		LogicHelper::PrintWStringFast(test);
	}
}

UIManager::~UIManager()
{
}


