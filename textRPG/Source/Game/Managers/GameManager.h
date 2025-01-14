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
			Instance.AssetHandlerInstance = std::make_shared<AssetHandler>();
		}

		if (Instance.UIManagerInstance == nullptr)
		{
			
			Instance.UIManagerInstance = std::make_shared<UIManager>();
			Instance.UIManagerInstance->Init();
		}

		if (Instance.TileMapIsntance == nullptr)
		{
			Instance.TileMapIsntance = std::make_shared<TileMap>(16, 8);
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

	bool IsClearGame() const
	{
		return bIsClearGame;
	}

	std::shared_ptr<UIManager>& GetUIManager()
	{
		return UIManagerInstance;
	}

	std::shared_ptr<AssetHandler>& GetAssetHandler()
	{
		return AssetHandlerInstance;
	}

	std::shared_ptr<TileMap>& GetTileMap()
	{
		return TileMapIsntance;
	}

	bool IsSpecialEventActivated() const
	{
		return bIsSpecialEventActivated;
	}

	void SetSpecialEventActive(bool bShouldActivate)
	{
		bIsSpecialEventActivated = bShouldActivate;
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
	bool bIsSpecialEventActivated;

	std::shared_ptr<UIManager> UIManagerInstance;

	std::shared_ptr<AssetHandler> AssetHandlerInstance;

	std::shared_ptr<TileMap> TileMapIsntance;
};