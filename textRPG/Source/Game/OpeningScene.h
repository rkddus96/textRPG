#pragma once

#include "IScene.h"

class OpeningScene : public IScene
{
public:

	OpeningScene();

	virtual void PlayScene() final;

	virtual ~OpeningScene() final;
};