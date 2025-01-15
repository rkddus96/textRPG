#pragma once
#include "IItem.h"
#include "Character.h"


class Shop
{
private:
	std::vector<std::shared_ptr<IItem>> ItemsForSale;

public:
	Shop();
	
	std::vector<std::shared_ptr<IItem>> GetItemsForSale() { return ItemsForSale; }

	// 유저가 Buy
	void BuyItem(Character& character, int& index);
	void SellItem(Character& character, int& index);

	// 상점 가기를 누르면 실행
	void ManageShop(Character& character);
	
	
	std::function<void(const std::vector<std::shared_ptr<IItem>>&)> OnItemsOfSaleChanged;



	
	void Display(int index);
};

