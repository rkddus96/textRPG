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
	MakeInventorySceneUI();

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
	
	BackgroundBorderLayer->DrawRectanlge(UI::BACKGRUOND_BORDER_FIRST_POSITION_X, UI::BACKGROUND_BORDER_FIRST_POSITION_Y, UI::BACKGROUND_BORDER_WIDTH, UI::BACKGROUND_BORDER_HEIGHT);
	BackgroundBorderLayer->CombineUiLines();

	std::shared_ptr<RenderingLayer> PressEnterKeyToStartLayer = std::make_shared<RenderingLayer>((int)EOpeningCanvasLayer::PressEnterKeyToStart, UI::USELESS_CHAR);
	OpeningCanvasLayerIdMap[EOpeningCanvasLayer::PressEnterKeyToStart] = PressEnterKeyToStartLayer->GetLayerId();

	PressEnterKeyToStartLayer->ClearLayerFor(UI::USELESS_CHAR);
	PressEnterKeyToStartLayer->DrawString(UI::PRESS_ENTER_KEY_TO_START_UI_POSITION_X, UI::PRESS_ENTER_KEY_TO_START_UI_POSITION_Y, L"Press Enter Key To Start Game");
	PressEnterKeyToStartLayer->CombineUiLines();

	std::shared_ptr<RenderingCanvas> OpeningCanvas = std::make_shared<RenderingCanvas>();
	OpeningCanvas->AddLayer(BackgroundArtLayer);
	OpeningCanvas->AddLayer(TitleLayer);
	OpeningCanvas->AddLayer(BackgroundBorderLayer);
	OpeningCanvas->AddLayer(PressEnterKeyToStartLayer);

	AddRenderingCanvas(ERenderingCanvas::Opening, OpeningCanvas);
}

void UIManager::MakeEndingSceneUI()
{
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

void UIManager::ChangeBasicCanvasStatInfoUI(ETempStatType StatType, int Amount, bool bShouldUpdateUI)
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
	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Basic);
	}
}

void UIManager::ChangeBasicCanvasArtImage(const std::vector<std::wstring>& Surface, bool bShouldUpdateUI)
{
	int ArtLayerId = BasicCanvasLayerIdMap[EBasicCanvasLayer::Art];
	std::shared_ptr<RenderingLayer> ArtLayer = RenderingCanvasMap[ERenderingCanvas::Basic]->GetRenderingLayer(ArtLayerId);

	if (ArtLayer == nullptr)
	{
		std::cout << "UIManager, ChangeBasicCanvasArtImage : Fail to get Layer" << std::endl;
		return;
	}

	ArtLayer->ClearLayerFor(UI::USELESS_CHAR);
	ArtLayer->DrawSurface(3, 20, Surface);

	ArtLayer->CombineUiLines();

	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Basic);
	}
}

void UIManager::ChangeBasicCanvasArtImage(const FASKIIArtContainer& ArtContainer, bool bShouldUpdateUI)
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
	ArtLayer->DrawSurface(DrawCoordX, DrawCoordY, ArtContainer.ArtLines);

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

void UIManager::SetOpeningCanvasTitleArt(int PositionX, int PositionY, const std::vector<std::wstring>& Surface, bool bShouldUpdateUI)
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

void UIManager::SetInventoryCanvasBackgroundImage(const FASKIIArtContainer& ArtContainer, bool bShouldUpdateUI)
{
	int LayerId = InventoryCanvasLayerIdMap[EInventoryCanvasLayer::Background];
	std::shared_ptr<RenderingLayer> InventoryLayer = RenderingCanvasMap[ERenderingCanvas::Inventory]->GetRenderingLayer(LayerId);

	if (InventoryLayer == nullptr)
	{
		std::cout << "UIManager, SetInventoryCanvasBackgroundImage : Fail to get Layer" << std::endl;
		return;
	}

	int CenterCoordX = (UI::EVENT_INFO_UI_BORDER_FIRST_POSITION_X - UI::BACKGRUOND_BORDER_FIRST_POSITION_X) / 2;
	int CenterCoordY = UI::BACKGROUND_BORDER_FIRST_POSITION_Y + UI::BACKGROUND_BORDER_WIDTH / 2;

	int ArtWidth = ArtContainer.GetWidth();
	int ArtHeight = ArtContainer.GetHeight();

	int DrawCoordX = CenterCoordX - ArtHeight / 2;
	int DrawCoordY = CenterCoordY - ArtWidth / 2;

	//InventoryLayer->ClearLayerFor(UI::USELESS_CHAR);

	InventoryLayer->DrawSurface(10, 10, ArtContainer.ArtLines);
	InventoryLayer->CombineUiLines();

	if (bShouldUpdateUI)
	{
		PrintUI(ERenderingCanvas::Inventory);
	}
}

void UIManager::SetInventoryCanvasItemList(const std::vector<std::shared_ptr<Item>>& InventoryInfo, bool bShouldUpdateUI)
{
	//InventoryInfo[1]->GetName()
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

void UIManager::SetMinimapUIContents()
{
	// TODO : 맵 타일 내용 받아서 그리기
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
				TileImage = L' ';
			}
			else if (TileTypeInfos[i][j] == ETile::Blank)
			{
				TileImage = L'O';
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


