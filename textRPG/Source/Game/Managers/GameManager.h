#pragma once

#include <memory>
#include "UIManager.h"
#include "../AssetHandler.h"
#include "../TileMap.h"

//class Monster;
//class BossMonster;

class GameManager
{
public:

	static GameManager& GetInstance()
	{
		static GameManager Instance;

		if (Instance.AssetHandlerInstance == nullptr)
		{
			Instance.AssetHandlerInstance = std::make_unique<AssetHandler>();
		}

		if (Instance.UIManagerInstance == nullptr)
		{
			
			Instance.UIManagerInstance = std::make_unique<UIManager>();
			Instance.UIManagerInstance->Init();
		}


		return Instance;
	}

	//std::unique_ptr<Monster> GenerateMonster(int Level);
	//std::unique_ptr<BossMonster> GenerateMonster(int Level);
	//void VisitShop();
	//bool IsBossStage();
	void ClearGame()
	{
		bIsClearGame = true;
	}

	bool GetIsClearGame() const
	{
		return bIsClearGame;
	}

	std::shared_ptr<UIManager>& GetUIManager()
	{
		return UIManagerInstance;
	}

	std::unique_ptr<AssetHandler>& GetAssetHandler()
	{
		return AssetHandlerInstance;
	}

	std::unique_ptr<TileMap>& GetTileMap()
	{
		return TileMapIsntance;
	}

private:

	GameManager();
	~GameManager();

	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	GameManager(GameManager&&) = delete;
	GameManager& operator=(GameManager&&) = delete;

private:
	
	bool bIsClearGame;

	std::shared_ptr<UIManager> UIManagerInstance;

	std::unique_ptr<AssetHandler> AssetHandlerInstance;

	std::unique_ptr<TileMap> TileMapIsntance;
};