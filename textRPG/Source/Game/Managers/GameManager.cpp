#include "GameManager.h"
#include "../Shop.h"

void GameManager::InitShop()
{
	ShopInstance = std::make_shared<Shop>();
}

GameManager::GameManager() :
	bIsClearGame(false),
	bIsSpecialEventActivated(false)
{
}

GameManager::~GameManager()
{
}
