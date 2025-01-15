#include "EndingScene.h"
#include "Managers/GameManager.h"
#include "Character.h"

EndingScene::EndingScene()
{
}

EndingScene::~EndingScene()
{
}

void EndingScene::PlayScene()
{
	if (Character::GetInstance().IsDead() && GameManager::GetInstance().IsClearGame() == false)
	{
		GameManager::GetInstance().GetUIManager()->ShowGameOverScene();
	}
}
