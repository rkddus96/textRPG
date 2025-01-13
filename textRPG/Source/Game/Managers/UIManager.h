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
	Ending

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

// 캐릭터 만들어질 때까지 임시
enum class ETempStatType
{
	Level,
	Hp,
	Defence,
	Power,
	Luck
};

enum class ETempTileType
{
	Block,
	Blank,
	DemonLordCastle,
	Village1,
	Village2,
	Village2_Disabled,
	Character
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
	void AddMessageToBasicCanvasEventInfoUI(const std::wstring& NewMessage);
	void ChangeBasicCanvasStatInfoUI(ETempStatType StatType, int Amount);
	void ChangeBasicCanvasArtImage(const std::vector<std::wstring>& Surface);
	void ChangeBasicCanvasArtImage(const struct FASKIIArtContainer& ArtContainer);
	void SetBasicCanvasLayerHide(bool bShouldHide, EBasicCanvasLayer LayerType);

	void SetOpeningCanvasTitleArt(int PositionX, int PositionY, const std::vector<std::wstring>& Surface);
	void SetOpeningCanvasLayerHide(bool bShouldHide, EOpeningCanvasLayer LayerType);

	void BindAllDelegate();

	// 임시 테스트용으로 퍼블릭 상태
	void OnMinimapUIContentsChanged(const std::vector<std::vector<ETempTileType>>& TileTypeInfos);

	
private:

	void Init();

	void MakeEmtpyCanvasUI();
	void MakeBasicUI();
	void MakeOpningSceneUI();

	void SetMinimapUIContents(/*std::vector<std::vector<Tile>> TileInfos*/);

	void Tick(double DeltaTime);

	void OnCharacterChanged(enum class ECharacterEvent CharacterEvent, int Amount);
	//std::function<void(EStat, int)> OnStatChanged;
	void OnStatChanged(enum class EStat StatType, int Amount);

private:


	std::unordered_map<ERenderingCanvas, std::shared_ptr<RenderingCanvas>> RenderingCanvasMap;
	
	std::unordered_map<EBasicCanvasLayer, int> BasicCanvasLayerIdMap;
	std::unordered_map<EOpeningCanvasLayer, int> OpeningCanvasLayerIdMap;

	std::deque<std::wstring> EventInfoUIContentsMsgs;

	std::vector<std::vector<wchar_t>> MinimapUIContents;

	friend class GameManager;
};