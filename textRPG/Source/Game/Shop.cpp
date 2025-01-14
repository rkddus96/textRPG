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



void Shop::ManageShop(Character& character)
{
	// 남은 골드 초기화
	int Gold = character.GetGold();
	
	//UI 변수 초기화
	std::shared_ptr<UIManager> UI = GameManager::GetInstance().GetUIManager();
	
	
	// 로그 선언
	std::string WelcomeLog;
	std::string FirstChoiceOptionsLog;
	std::string PurchaseLog;
	std::string SellLog;
	std::string BackToFirstChoiceLog;
	std::string GetOutShopLog;
	std::string WrongChoiceLog;
	std::string RemainGoldLog;
	std::wstring WelcomeLogW;
	std::wstring FirstChoiceOptionsLogW;
	std::wstring PurchaseLogW;
	std::wstring SellLogW;
	std::wstring BackToFirstChoiceLogW;
	std::wstring GetOutShopLogW;
	std::wstring WrongChoiceLogW;
	std::wstring RemainGoldLogW;


	// 로그 초기화
	WelcomeLog = "안녕하세요! 무엇을 도와드릴까요?";
	FirstChoiceOptionsLog = 
	 "(1) 구매한다.\n"
	 "(2) 판매한다.\n"
     "(3) 나간다.\n";

	PurchaseLog = 
	    "어떤 물품을 원하시나요? 원하는 번호를 입력해주세요. \n";
		"0: 뒤로 가기";

	SellLog = 
	    "어떤 물품을 파실건가요? 파실 물품의 번호를 입력해주세요.\n";
		"0: 뒤로 가기";

	BackToFirstChoiceLog = 
	   "첫 번째 선택으로 돌아갑니다.";

	GetOutShopLog =
		"상점에서 나갑니다. 다음에 또 오세요!";

	WrongChoiceLog =
		"잘못된 선택입니다. 다시 입력해주세요.";

	RemainGoldLog =
		"남은 골드: " + std::to_string(Gold);


	
	WelcomeLogW = LogicHelper::StringToWString(WelcomeLog);
	FirstChoiceOptionsLogW = LogicHelper::StringToWString(FirstChoiceOptionsLog);
	PurchaseLogW = LogicHelper::StringToWString(PurchaseLog);
	SellLogW = LogicHelper::StringToWString(SellLog);
	BackToFirstChoiceLogW = LogicHelper::StringToWString(BackToFirstChoiceLog);
	GetOutShopLogW = LogicHelper::StringToWString(GetOutShopLog);
	WrongChoiceLogW = LogicHelper::StringToWString(WrongChoiceLog);
	RemainGoldLogW = LogicHelper::StringToWString(RemainGoldLog);


	// 로그 출력
	UI->AddMessageToBasicCanvasEventInfoUI(WelcomeLogW);
	
	while (true) {
		
	//	std::cout << FirstChoiceOptionsLog;
		UI->AddMessageToBasicCanvasEventInfoUI(FirstChoiceOptionsLogW);

		// 입력값 초기화
		int Choice;
		int ItemChoice;
		std::cin >> Choice;

		switch (Choice) {
			case 1: // 구매
			//	std::cout << PurchaseLog << std::endl;
				// 구매
				while (true)
				{
					UI->AddMessageToBasicCanvasEventInfoUI(PurchaseLogW);
					// 사용자 소지 돈 초기화
					Gold = character.GetGold();
					Display();
					std::cin >> ItemChoice;
					if (ItemChoice == 0)
					{
						break;
					}
					if (ItemChoice > ItemsForSale.size())
					{
						UI->AddMessageToBasicCanvasEventInfoUI(WrongChoiceLogW);
					}
					else
					{
						BuyItem(character, ItemChoice - 1);
					}
					
					
				}
				break;

			case 2: // 판매
			
				while (true)
				{
					UI->AddMessageToBasicCanvasEventInfoUI(SellLogW);
					Gold = character.GetGold();
					Display();
					UI->AddMessageToBasicCanvasEventInfoUI(RemainGoldLogW);
				
					std::cin >> ItemChoice;
					if (ItemChoice == 0)
					{
						break;
					}
					if (ItemChoice > ItemsForSale.size())
					{
						UI->AddMessageToBasicCanvasEventInfoUI(WrongChoiceLogW);
					}
					else
					{
						SellItem(character, ItemChoice - 1);
					}
					
					
				}
				break;

			case 3: // 나가기
				UI->AddMessageToBasicCanvasEventInfoUI(GetOutShopLogW);
				return;

			default:
				UI->AddMessageToBasicCanvasEventInfoUI(WrongChoiceLogW);
				break;
		}
	}


	
}






void Shop::Display()
{
	std::shared_ptr<UIManager> UI = GameManager::GetInstance().GetUIManager();


	std::string ItemNameLog;
	std::string ItemPriceLog;
	std::string	ItemExplanationLog;

	std::wstring ItemNameLogW;
	std::wstring ItemPriceLogW;
	std::wstring ItemExplanationLogW;

	ItemNameLogW = LogicHelper::StringToWString(ItemNameLog);
	ItemPriceLogW = LogicHelper::StringToWString(ItemPriceLog);
	ItemExplanationLogW = LogicHelper::StringToWString(ItemExplanationLog);


	for (int i = 0; i < ItemsForSale.size(); i++)
	{
		ItemNameLog = std::to_string(i + 1) + ". Name: " + ItemsForSale[i]->GetName() +"\n";
		ItemPriceLog = "  Price: " + std::to_string(ItemsForSale[i]->GetPrice()) + "\n";
		ItemExplanationLog = "  Explanation: " + ItemsForSale[i]->GetExplanation() + "\n";
		
		UI->AddMessageToBasicCanvasEventInfoUI(ItemNameLogW);
		UI->AddMessageToBasicCanvasEventInfoUI(ItemPriceLogW);
		UI->AddMessageToBasicCanvasEventInfoUI(ItemExplanationLogW);
		
		std::cout << i+1 << ". Name: " << ItemsForSale[i]->GetName() << std::endl;
		std::cout << "  Price: " << ItemsForSale[i]->GetPrice() << std::endl;
		std::cout << "  Explanation: " << ItemsForSale[i]->GetExplanation() << std::endl;
	}
	
}
