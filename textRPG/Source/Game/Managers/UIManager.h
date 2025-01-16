#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include <deque>
#include "../LogicHelper.h"

class RenderingLayer;
class RenderingCanvas;

enum class ERenderingCanvas
{
	Empty,
	Basic,
	Opening,
	Ending,
	Inventory
};

/// <summary>
/// LayerOrder 순으로 선언되어 있다.
/// </summary>
enum class EBasicCanvasLayer
{
	BackgroundBorder,
	MinimapContents,
	Art,
	Vfx,
	MinimapBorder,
	EventInfoUIBorder,
	EventInfoUIContents,
	StatInfo,
	MonsterInfo
};

/// <summary>
/// LayerOrder 순으로 선언되어 있다.
/// </summary>
enum class EOpeningCanvasLayer
{
	BackgroundBorder,
	BackgroundArt,
	Title,
	PressEnterKeyToStart,
	PrologBackground,
	PrologueText,
};

/// <summary>
/// LayerOrder 순으로 선언되어 있다.
/// </summary>
enum class EEndingCanvasLayer
{
	Background,
	BackgroundArt,
	GameOver,
	ThankYouForPlaying,
	EpilogueBackground,
	EpilogueText,
};

enum class EInventoryCanvasLayer
{
	Background,
	ItemList
};

enum class EUIColor
{
	Black,
	Blue,
	Green,
	Aqua,
	Red,
	Purple,
	Yellow,
	White_Default,
	Gray,
	LightBlue,
	LightGreen,
	LightAqua,
	LightRed,
	LightYellow,
	BrightWhite
};

enum class ETile;
struct FASCIIArtContainer;
class IItem;
enum class EStat;
class Monster;
enum class ECharacterEvent;
enum class EStat;

struct FStoryTextContainer
{
	void AddTextLine(const std::string& NewText)
	{
		AddTextLine(LogicHelper::StringToWString(NewText));
	}

	void AddTextLine(const std::wstring& NewText)
	{
		StoryTextLines.push_back(NewText);
	}

	std::vector<std::wstring> StoryTextLines;
};

class UIManager
{
public:

	UIManager();
	~UIManager();

	UIManager(const UIManager&) = delete;
	UIManager& operator=(const UIManager&) = delete;
	UIManager(UIManager&&) = delete;
	UIManager& operator=(UIManager&&) = delete;

	
	void AddRenderingCanvas(ERenderingCanvas CanvasType, std::shared_ptr<RenderingCanvas> NewRenderingCanvas);
	void PrintUI(ERenderingCanvas CanvasType);

	//void SetMiniMapUI(std::vector<std::wstring>& MapInfos);
	void AddMessageToBasicCanvasEventInfoUI(const std::wstring& NewMessage, bool bShouldUpdateUI = true);
	void ClearMessageToBasicCanvasEventInfoUI(bool bShouldUpdateUI = true);

	void ChangeBasicCanvasJobInfoUI(int JobChoice, bool bShouldUpdateUI = true);
	void ChangeBasicCanvasLevelInfoUI(int Amount, bool bShouldUpdateUI = true);
	void ChangeBasicCanvasExpInfoUI(int Amount, bool bShouldUpdateUI = true);
	void ChangeBasicCanvasMaxExpInfoUI(int Amount, bool bShouldUpdateUI = true);
	void ChangeBasicCanvasMoneyInfoUI(int Amount, bool bShouldUpdateUI = true);

	void ChangeBasicCanvasStatInfoUI(EStat StatType, int Amount, bool bShouldUpdateUI = true);
	void ChangeBasicCanvasArtImage(const FASCIIArtContainer& ArtContainer, bool bShouldUpdateUI = true, int OffsetX = 0, int OffsetY = 0);
	void SetBasicCanvasLayerHide(bool bShouldHide, EBasicCanvasLayer LayerType, bool bShouldUpdateUI = true);
	// 몬스터 이름은 영어로 되어있어야 가운데 맞춤이 정상적으로 이루어짐.
	void SetBasicCanvasMonsterInfoUI(const std::string& MonsterName, int MonsterHp, bool bShouldUpdateUI = true);

	//void SetOpeningCanvasTitleArt(int PositionX, int PositionY, const std::vector<std::wstring>& Surface, bool bShouldUpdateUI = true);
	void SetOpeningCanvasTitleArt(int PositionX, int PositionY, const FASCIIArtContainer& ArtContainer, bool bShouldUpdateUI = true);
	void SetOpeningCanvasBackgroundArt(int PositionX, int PositionY, const std::vector<std::wstring>& Surface, bool bShouldUpdateUI = true);
	void SetOpeningCanvasLayerHide(bool bShouldHide, EOpeningCanvasLayer LayerType, bool bShouldUpdateUI = true);
	void SetOpeningCanvasPrologueBackgroundArt(const FASCIIArtContainer& ArtContainer, bool bShouldUpdateUI = true, int OffsetX = 0, int OffsetY = 0);
	void SetOpeningCanvasPrologueText(const FStoryTextContainer& StoryTextConatiner, int PositionX, int PositionY, bool bShouldUpdateUI = true);
	void DrawOpeningCanvasPrologue(const FStoryTextContainer& StoryTextConatiner, bool bShouldUpdateUI = true, int OffsetX = 0, int OffsetY = 0);

	void SetInventoryCanvasBackgroundImage(const FASCIIArtContainer& ArtContainer, bool bShouldUpdateUI = true, int OffsetX = 0, int OffsetY = 0);
	void SetInventoryCanvasItemList(const std::vector<std::shared_ptr<IItem>>& InventoryInfo, int PositionX, int PositionY, bool bShouldUpdateUI = true);
	void DrawInventory(const std::vector<std::shared_ptr<IItem>>& InventoryInfo, bool bShouldUpdateUI = true, int OffsetX = 0, int OffsetY = 0);

	void OpenInventory();

	void SetEndingCanvasLayerHide(bool bShouldHide, EEndingCanvasLayer LayerType, bool bShouldUpdateUI = true);
	void SetEndingCanvasEpilogueBackground(const FASCIIArtContainer& ArtContainer, bool bShouldUpdateUI = true, int OffsetX = 0, int OffsetY = 0);
	void SetEndingCanvasEpilogueText(const FStoryTextContainer& StoryTextConatiner, int PositionX, int PositionY, bool bShouldUpdateUI = true);
	void DrawEndingCanvasPrologue(const FStoryTextContainer& StoryTextConatiner, bool bShouldUpdateUI = true, int OffsetX = 0, int OffsetY = 0);

	void ShowGameOverScene();


	void SetConsoleColor(EUIColor UIColor);

	void BindAllDelegate();

private:

	void Init();

	void MakeEmtpyCanvasUI();
	void MakeBasicUI();
	void MakeOpningSceneUI();
	void MakeEndingSceneUI();
	void MakeInventorySceneUI();

	void SetMinimapUIContents(/*std::vector<std::vector<ETile>> TileInfos*/);

	void Tick(double DeltaTime);

	void OnCharacterChanged(ECharacterEvent CharacterEvent, int Amount);

	void OnStatChanged(EStat StatType, int Amount);
	void OnMinimapUIContentsChanged(const std::vector<std::vector<ETile>>& TileTypeInfos);

private:


	std::unordered_map<ERenderingCanvas, std::shared_ptr<RenderingCanvas>> RenderingCanvasMap;
	
	std::unordered_map<EBasicCanvasLayer, int> BasicCanvasLayerIdMap;
	std::unordered_map<EOpeningCanvasLayer, int> OpeningCanvasLayerIdMap;
	std::unordered_map<EEndingCanvasLayer, int> EndiningCanvasLayerIdMap;
	std::unordered_map<EInventoryCanvasLayer, int> InventoryCanvasLayerIdMap;

	std::deque<std::wstring> EventInfoUIContentsMsgs;

	std::vector<std::vector<wchar_t>> MinimapUIContents;

	int CurrentHpUIInfo = 0;
	int MaxHpUIInfo = 0;

	int CurrentExpUIInfo = 0;
	int MaxExpUIInfo = 0;


	friend class GameManager;
};