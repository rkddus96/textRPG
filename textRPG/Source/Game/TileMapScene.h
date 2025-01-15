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

	virtual void DrawField();
	bool IsMoveInput(EKey KeyInput) const;
	bool IsInventoryInput(EKey KeyInput) const;
	std::pair<int, int> CalculateNextPosition(std::pair<int, int> CurrentPosition, EKey KeyInput);
};