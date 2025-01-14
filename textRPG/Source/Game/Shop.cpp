#include "Shop.h"
#include <iostream>
#include <string>
#include <memory>
#include <Windows.h>

#include "HealthPotion.h"
#include "Equipment.h"
#include "./Managers/GameManager.h"
#include "./LogicHelper.h"
#include "./InputReceiver.h"
#include "./Managers/UIManager.h"



Shop::Shop()
{
	// Potion index는 항상 0
	ItemsForSale.emplace_back(std::make_shared<HealthPotion>("Potion", 200));
	
	// 저급 아이템
	ItemsForSale.emplace_back(std::make_shared<Equipment>("Helmet", EStat::Defense, 2, 1200));
	ItemsForSale.emplace_back(std::make_shared<Equipment>("Armor", EStat::Defense, 2, 1200));
	ItemsForSale.emplace_back(std::make_shared<Equipment>("Axe", EStat::Power, 3, 1200));
	ItemsForSale.emplace_back(std::make_shared<Equipment>("Sword", EStat::Power, 3, 1200));
	ItemsForSale.emplace_back(std::make_shared<Equipment>("Short Sword", EStat::Luck, 3, 1200));
	
	// 고급 아이템
	ItemsForSale.emplace_back(std::make_shared<Equipment>("Ragnarok's Edge", EStat::Power, 18, 6000));
	ItemsForSale.emplace_back(std::make_shared<Equipment>("Yggdrasil's Branch", EStat::Defense, 12, 6000));
	ItemsForSale.emplace_back(std::make_shared<Equipment>("Loki's Charm", EStat::Luck, 18, 6000));
}

void Shop::BuyItem(Character& character, int index)
{
	std::vector<std::shared_ptr<IItem>> Inventory = character.GetInventory();
	int Gold = character.GetGold();
	int Price = ItemsForSale[index]->GetPrice();

	if (Gold < Price)
	{
		std::cout << "돈이 부족합니다." << std::endl;
		return;
	}
	else
	{
		// 인벤토리에 상품 넣기, 골드 차감
		Inventory.push_back(ItemsForSale[index]);
		character.SetGold(Gold - Price );

		if (OnItemChanged)
		{
			OnItemChanged(Inventory);
		}


		// 포션이 아닐 경우
		if (index != 0)
		{
			// 아이템 목록에서 상품 제거
			ItemsForSale.erase(ItemsForSale.begin() + index);
		}

		if (OnItemChanged)
		{
			OnItemChanged(ItemsForSale);
		}
	}

	
	
}

void Shop::SellItem(Character& character, int index)
{
	std::vector<std::shared_ptr<IItem>> Inventory = character.GetInventory();
	int Gold = character.GetGold();
	int Price = ItemsForSale[index]->GetPrice();

	// 포션이 아닐 경우
	if (index != 0)
	{
		// 상점에 상품 넣기
		ItemsForSale.push_back(Inventory[index]);
		Inventory[index]->UnUse(character);


		if (OnItemChanged)
		{
			OnItemChanged(ItemsForSale);
		}
		
	}

	// 인벤토리에서 상품 제거, 반값만큼 골드 증가
	Inventory.erase(Inventory.begin() + index);
	character.SetGold(Gold - (Price / 2));
	
	if (OnItemChanged)
	{
		OnItemChanged(Inventory);
	}
}


/*
void Shop::ManageShop(Character& character)
{
	//UI 변수 초기화
	std::shared_ptr<UIManager> UI = GameManager::GetInstance().GetUIManager();
	
	
	// 로그 선언
	std::string WelcomeLog;
	std::string FirstChoiceOptionsLog;
	std::string PurchaseLog;
	std::string SellLog;
	std::string BackToFirstChoiceLog;
	std::wstring WelcomeLogW;
	std::wstring FirstChoiceOptionsLogW;
	std::wstring PurchaseLogW;
	std::wstring SellLogW;
	std::wstring BackToFirstChoiceLogW;


	// 로그 초기화
	WelcomeLog = "안녕하세요! 무엇을 도와드릴까요?";
	FirstChoiceOptionsLog = 
	 "(1) 구매한다.\n"
	 "(2) 판매한다.\n"
     "(3) 나간다.\n";

	PurchaseLog = 
	    "어떤 물품을 원하시나요? 원하는 번호를 입력해주세요.";

	SellLog = 
	    "어떤 물품을 파실건가요? 파실 물품의 번호를 입력해주세요.";

	BackToFirstChoiceLog = 
	   "첫 번째 선택으로 돌아갑니다.";
	WelcomeLogW = LogicHelper::StringToWString(WelcomeLog);
	FirstChoiceOptionsLogW = LogicHelper::StringToWString(FirstChoiceOptionsLog);
	PurchaseLogW = LogicHelper::StringToWString(PurchaseLog);
	SellLogW = LogicHelper::StringToWString(SellLog);
	BackToFirstChoiceLogW = LogicHelper::StringToWString(BackToFirstChoiceLog);


	// 로그 출력
	UI->AddMessageToBasicCanvasEventInfoUI(WelcomeLogW);

	while (true) {
		
	//	std::cout << WelcomeLog << std::endl;
		UI->AddMessageToBasicCanvasEventInfoUI(WelcomeLogW);
	//	std::cout << FirstChoiceOptionsLog;
		UI->AddMessageToBasicCanvasEventInfoUI(FirstChoiceOptionsLogW);

		int choice;
		std::cin >> choice;

		switch (choice) {
			case 1: // 구매
			//	std::cout << PurchaseLog << std::endl;
				UI->AddMessageToBasicCanvasEventInfoUI(PurchaseLogW);
				// 구매
				break;

			case 2: // 판매
			//	std::cout << SellLog << std::endl;
				UI->AddMessageToBasicCanvasEventInfoUI(SellLogW);
				// 판매
				break;

			case 3: // 나가기
				std::cout << "상점에서 나갑니다. 다음에 또 오세요!" << std::endl;
				return;

			default:
				std::cout << "잘못된 선택입니다. 다시 입력해주세요." << std::endl;
				break;
		}
	}


	
}
*/





void Shop::Display()
{
	for (auto item : ItemsForSale)
	{
		std::cout << "   Name: " << item->GetName() << std::endl;
		std::cout << "   Price: " << item->GetPrice() << std::endl;
		std::cout << "   Explanation: " << item->GetExplanation() << std::endl;
	}
	
}
