#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include <deque>

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
	MinimapContents,
	Art,
	Vfx,
	BackgroundBorder,
	MinimapBorder,
	EventInfoUIBorder,
	EventInfoUIContents,
	StatInfo
};

/// <summary>
/// LayerOrder 순으로 선언되어 있다.
/// </summary>
enum class EOpeningCanvasLayer
{
	BackgroundArt,
	Title,
	BackgroundBorder,
	PressEnterKeyToStart,
};

/// <summary>
/// LayerOrder 순으로 선언되어 있다.
/// </summary>
enum class EEndingCanvasLayer
{

};

enum class EInventoryCanvasLayer
{
	Background,
	ItemList
};

// 캐릭터 만들어질 때까지 임시
enum class ETempStatType
{
	Level,
	Hp,
	Defence,
	Power,
	Luck
};

enum class ETile;
struct FASKIIArtContainer;
class Item;

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
	void ChangeBasicCanvasStatInfoUI(ETempStatType StatType, int Amount, bool bShouldUpdateUI = true);
	void ChangeBasicCanvasArtImage(const std::vector<std::wstring>& Surface, bool bShouldUpdateUI = true);
	void ChangeBasicCanvasArtImage(const FASKIIArtContainer& ArtContainer, bool bShouldUpdateUI = true);
	void SetBasicCanvasLayerHide(bool bShouldHide, EBasicCanvasLayer LayerType, bool bShouldUpdateUI = true);

	void SetOpeningCanvasTitleArt(int PositionX, int PositionY, const std::vector<std::wstring>& Surface, bool bShouldUpdateUI = true);
	void SetOpeningCanvasBackgroundArt(int PositionX, int PositionY, const std::vector<std::wstring>& Surface, bool bShouldUpdateUI = true);
	void SetOpeningCanvasLayerHide(bool bShouldHide, EOpeningCanvasLayer LayerType, bool bShouldUpdateUI = true);

	void SetInventoryCanvasBackgroundImage(const FASKIIArtContainer& ArtContainer, bool bShouldUpdateUI = true);
	void SetInventoryCanvasItemList(const std::vector<std::shared_ptr<Item>>& InventoryInfo, bool bShouldUpdateUI = true);

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

	void OnCharacterChanged(enum class ECharacterEvent CharacterEvent, int Amount);
	//std::function<void(EStat, int)> OnStatChanged;
	void OnStatChanged(enum class EStat StatType, int Amount);
	void OnMinimapUIContentsChanged(const std::vector<std::vector<ETile>>& TileTypeInfos);

private:


	std::unordered_map<ERenderingCanvas, std::shared_ptr<RenderingCanvas>> RenderingCanvasMap;
	
	std::unordered_map<EBasicCanvasLayer, int> BasicCanvasLayerIdMap;
	std::unordered_map<EOpeningCanvasLayer, int> OpeningCanvasLayerIdMap;
	std::unordered_map<EEndingCanvasLayer, int> EndiningCanvasLayerIdMap;
	std::unordered_map<EInventoryCanvasLayer, int> InventoryCanvasLayerIdMap;

	std::deque<std::wstring> EventInfoUIContentsMsgs;

	std::vector<std::vector<wchar_t>> MinimapUIContents;

	friend class GameManager;
};