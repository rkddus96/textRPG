#pragma once

#include <utility>
#include "IScene.h"
#include "InputReceiver.h"

class TileMapScene : public IScene
{
public:
	TileMapScene();
	virtual ~TileMapScene() final;

	virtual void PlayScene() final;

protected:
	virtual void DrawField();
	bool IsMoveInput(EKey KeyInput) const;
	std::pair<int, int> CalculateNextPosition(std::pair<int, int> CurrentPosition, EKey KeyInput);
};