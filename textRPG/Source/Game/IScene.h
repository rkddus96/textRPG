#pragma once

class IScene
{
public:

	IScene();

	virtual ~IScene() = 0;

	virtual void PlayScene() = 0;
};