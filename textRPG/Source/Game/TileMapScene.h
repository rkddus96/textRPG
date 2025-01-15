#pragma once

#include <utility>
#include "IScene.h"
#include "InputReceiver.h"
#include "AssetHandler.h"

class TileMapScene : public IScene
{
public:
	TileMapScene();
	virtual ~TileMapScene() final;

	virtual void PlayScene() final;

protected:
	/// <summary>
	/// 필드에서 적과의 전투 발생 확률, [0, 1]
	/// </summary>
	double EncounterProbability = 0.5;
	/// <summary>
	/// Tile 이동 후의 딜레이, ms
	/// </summary>
	int MoveDelay = 500;

	/// <summary>
	/// 화면이 무효화되었는지 체크하는 변수, true일 경우 새로운 Scene을 그린다.
	/// 매 프레임 변화가 있을 것이므로 매 프레임 true로 초기화한다.
	/// 만약에 특정 행동에서 출력을 마무리 짓고 더 이상 출력할 필요가 없다면 false로 설정해서 다시 타일로 재입장하는 것을 방지한다.
	/// </summary>
	bool bIsSceneInvalid = true;
	virtual void DrawField();

	bool IsMoveInput(EKey KeyInput) const;
	bool IsInventoryInput(EKey KeyInput) const;
	bool IsInteractionInput(EKey KeyInput) const;

	std::pair<int, int> CalculateNextPosition(std::pair<int, int> CurrentPosition, EKey KeyInput);
	std::vector<std::wstring> SplitByNewLine(const std::wstring& Str);
};