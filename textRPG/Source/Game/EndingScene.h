#pragma once

#include "IScene.h"

class EndingScene : public IScene
{
public:
	EndingScene();

	~EndingScene() override;

	virtual void PlayScene() override;

	void PlayNormalEndingEpilogue();
	void PlayTrueEndingEpilogue();
};