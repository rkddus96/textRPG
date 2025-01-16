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
#include "InputReceiver.h"
#include "AssetHandler.h"




Shop::Shop()
{
	// Potion index는 항상 0
	ItemsForSale.emplace_back(std::make_shared<HealthPotion>("Potion", 200, GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Potion)));
	
	// 저급 아이템
	ItemsForSale.emplace_back(std::make_shared<Equipment>("Helmet", std::vector<EStat>{ EStat::Defense }, std::vector<int>{ 2 }, 1200, GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Helmet)));
	ItemsForSale.emplace_back(std::make_shared<Equipment>("Armor", std::vector<EStat>{EStat::Defense}, std::vector<int>{ 2 }, 1200, GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Armor)));
	ItemsForSale.emplace_back(std::make_shared<Equipment>("Axe", std::vector<EStat>{ EStat::Power }, std::vector<int>{ 3 }, 1200, GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Axe)));
	ItemsForSale.emplace_back(std::make_shared<Equipment>("Sword", std::vector<EStat>{ EStat::Power }, std::vector<int>{ 3 }, 1200, GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Sword)));
	ItemsForSale.emplace_back(std::make_shared<Equipment>("Short Sword", std::vector<EStat>{ EStat::Luck }, std::vector<int>{ 3 }, 1200, GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::ShortSword)));
	
	// 고급 아이템
	ItemsForSale.emplace_back(std::make_shared<Equipment>("Ragnarok's Edge", std::vector<EStat>{ EStat::Power }, std::vector<int>{ 18 }, 6000, GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Sword2)));
	ItemsForSale.emplace_back(std::make_shared<Equipment>("Yggdrasil's Branch", std::vector<EStat>{ EStat::Defense }, std::vector<int>{ 15 }, 6000, GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Wand)));
	ItemsForSale.emplace_back(std::make_shared<Equipment>("Loki's Charm", std::vector<EStat>{ EStat::Luck }, std::vector<int>{ 18 }, 6000, GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Necklace)));

	// 극단적인 아이템
//	ItemsForSale.emplace_back(std::make_shared<Equipment>("Blood Axe", std::vector<EStat>{ EStat::Power, EStat::Defense }, std::vector<int>{ 36, -12 }, 6000, GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Clock)));
}



void Shop::BuyItem(Character& character, int& index)
{
	std::shared_ptr<UIManager> UI = GameManager::GetInstance().GetUIManager();

	std::string CannotBuyLogOne;
	std::string CannotBuyLogTwo;
	std::wstring CannotBuyLogOneW;
	std::wstring CannotBuyLogTwoW;

	CannotBuyLogOne = "돈이 부족합니다.";
	CannotBuyLogTwo = "더 이상 아이템을 구매할 수 없습니다.";
	
	CannotBuyLogOneW = LogicHelper::StringToWString(CannotBuyLogOne);
	CannotBuyLogTwoW = LogicHelper::StringToWString(CannotBuyLogTwo);

	std::vector<std::shared_ptr<IItem>>& Inventory = character.GetInventory();
	int Gold = character.GetGold();
	int Price = ItemsForSale[index]->GetPrice();

	// 인벤토리가 가득 차지 않은 경우
	if (Inventory.size() <= 9)
	{
		if (Gold < Price)
		{
			UI->ClearMessageToBasicCanvasEventInfoUI(false);
			UI->AddMessageToBasicCanvasEventInfoUI(CannotBuyLogOneW);
			Sleep(500);
			return;
		}
		else
		{
			// 인벤토리에 상품 넣기, 골드 차감
			
			Inventory.push_back(ItemsForSale[index]);
			character.SetGold(Gold - Price);

			// 포션이 아닐 경우
			if (index != 0)
			{
				ItemsForSale[index]->IsUsed(character);
				// 아이템 목록에서 상품 제거
				ItemsForSale.erase(ItemsForSale.begin() + index);
				if (index >= ItemsForSale.size())
				{
					index = max(0, static_cast<int>(ItemsForSale.size()) - 1);
				}
				// 아이템 효과 적용
				
				// ItemIndex가 벡터의 새로운 크기를 초과하지 않도록 조정
				
			}
		}
	}
	// 인벤토리가 가득 찬 경우
	else
	{
		UI->ClearMessageToBasicCanvasEventInfoUI(false);
		UI->AddMessageToBasicCanvasEventInfoUI(CannotBuyLogTwoW);
		Sleep(500);
	}


	
}

void Shop::SellItem(Character& character, int& index)
{
	std::vector<std::shared_ptr<IItem>>& Inventory = character.GetInventory();
	int Gold = character.GetGold();
	int Price = Inventory[index]->GetPrice();

	// 포션이 아닐 경우
	if (index != 0)
	{
		// 상점에 상품 넣기
		ItemsForSale.push_back(Inventory[index]);
		Inventory[index]->UnUse(character);
		
	}

	// 인벤토리에서 상품 제거, 반값만큼 골드 증가
	Inventory.erase(Inventory.begin() + index);
	
	// ItemIndex가 벡터의 새로운 크기를 초과하지 않도록 조정
	if (index >= Inventory.size())
	{
		index = max(0, static_cast<int>(Inventory.size()) - 1);
	}


	character.SetGold(Gold + (Price / 2));
	

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
	FirstChoiceOptionsLog = "[ <-. 구매한다. ][ ->. 판매한다. ] [ x. 나가기   ]";

	/*PurchaseLog = "어떤 물품을 원하시나요? 원하는 번호를 입력해주세요.    x: 뒤로 가기";
		
	SellLog = "어떤 물품을 파실건가요? 파실 물품의 번호를 입력해주세요.    x: 뒤로 가기";*/

	BackToFirstChoiceLog = "첫 번째 선택으로 돌아갑니다.";

	GetOutShopLog = "상점에서 나갑니다. 다음에 또 오세요!";

	WrongChoiceLog = "잘못된 선택입니다. 다시 입력해주세요.";

	RemainGoldLog = "남은 골드: " + std::to_string(Gold);

	
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
	
	// 이미지 초기화
	const FASCIIArtContainer& ArtContainer = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::StoreLarge);
	const FASCIIArtContainer& ArtContainerTwo = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Merchant);
//	GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::MerchantTwo);

	// 상점 출력
	UI->ChangeBasicCanvasArtImage(ArtContainer);


	while (true) {
		
		// 로그 초기화
		UI->ClearMessageToBasicCanvasEventInfoUI(false);

		// 상인 이미지 출력
		UI->ChangeBasicCanvasArtImage(ArtContainerTwo);
		UI->AddMessageToBasicCanvasEventInfoUI(FirstChoiceOptionsLogW);

		// 입력값 초기화
	//	int Choice;
	//	int ItemChoice;
		int ItemIndex = 0;
		
		
		EKey Choice = InputReceiver::ChatchInput();
//		std::cin >> Choice;

		switch (Choice) {
		case EKey::LeftArrow: // 구매
				// 구매
				while (true)
				{
				//	UI->AddMessageToBasicCanvasEventInfoUI(PurchaseLogW);
					// 사용자 소지 돈 초기화
					Gold = character.GetGold();
				//	Display();
					//		UI->AddMessageToBasicCanvasEventInfoUI(PurchaseLogW);


					UI->ClearMessageToBasicCanvasEventInfoUI(false);
					Display(ItemIndex);
					// 사용자 소지 돈 초기화, 출력
				//	Gold = character.GetGold();
				//	RemainGoldLog = "남은 골드: " + std::to_string(Gold);
				//	RemainGoldLogW = LogicHelper::StringToWString(RemainGoldLog);
				//	UI->AddMessageToBasicCanvasEventInfoUI(RemainGoldLogW);
				//	std::cin >> ItemChoice;
					EKey ItemChoice = InputReceiver::ChatchInput();

					switch (ItemChoice)
					{
					case EKey::x: // 뒤로
						break;

					case EKey::LeftArrow: // 전 페이지
						if (ItemIndex > 0)
						{
							ItemIndex--;
						}
						else
						{
							UI->ClearMessageToBasicCanvasEventInfoUI(false);
							UI->AddMessageToBasicCanvasEventInfoUI(WrongChoiceLogW);
							Sleep(500);
						}
						break;

					case EKey::z: // 아이템 구매
						BuyItem(character, ItemIndex);
						break;

					case EKey::RightArrow: // 다음 페이지
						if (ItemIndex < ItemsForSale.size() - 1)
						{
							ItemIndex++;
						}
						else
						{
							UI->ClearMessageToBasicCanvasEventInfoUI(false);
							UI->AddMessageToBasicCanvasEventInfoUI(WrongChoiceLogW);
							Sleep(500);
						}
						break;

					default: // 잘못된 선택
						UI->AddMessageToBasicCanvasEventInfoUI(WrongChoiceLogW);
						Sleep(500);
						break;
					}

					if (ItemChoice == EKey::x)
					{
						break;
					}
				}
				break;

			case EKey::RightArrow: // 판매

				if (character.GetInventory().empty())
				{
					UI->AddMessageToBasicCanvasEventInfoUI(L"인벤토리에 아이템이 없습니다.");
					Sleep(500);
					break;
				}
				else
				{
					// 캐릭터의 인벤토리가 비어있을 경우 접근 X
					while (true)
					{
						if (character.GetInventory().empty())
						{
							UI->AddMessageToBasicCanvasEventInfoUI(L"인벤토리에 아이템이 없습니다.");
							Sleep(500);
							break;
						}
						//	UI->AddMessageToBasicCanvasEventInfoUI(SellLogW);
						Gold = character.GetGold();
						//	character.DisplayInventory();
						//	UI->AddMessageToBasicCanvasEventInfoUI(RemainGoldLogW);
							//		UI->AddMessageToBasicCanvasEventInfoUI(SellLogW);

						UI->ClearMessageToBasicCanvasEventInfoUI(false);
						character.DisplayInventory(ItemIndex);
						//		Gold = character.GetGold();
						//		RemainGoldLog = "남은 골드: " + std::to_string(Gold);
						//		RemainGoldLogW = LogicHelper::StringToWString(RemainGoldLog);
						//		UI->AddMessageToBasicCanvasEventInfoUI(RemainGoldLogW);

						EKey ItemChoice = InputReceiver::ChatchInput();

						//	std::cin >> ItemChoice;
						switch (ItemChoice)
						{
						case EKey::x: // 뒤로
							break;

						case EKey::LeftArrow: // 전 페이지
							if (ItemIndex > 0)
							{
								ItemIndex--;
							}
							else
							{
								UI->AddMessageToBasicCanvasEventInfoUI(WrongChoiceLogW);
							}
							break;

						case EKey::z: // 아이템 판매
							SellItem(character, ItemIndex);

							if (character.GetInventory().empty())
							{
								ItemChoice = EKey::Key_0; // 모두 팔렸을 경우 전 페이지로 이동
							}

							break;

						case EKey::RightArrow: // 다음 페이지
							if (ItemIndex < character.GetInventory().size() - 1)
							{
								ItemIndex++;
							}
							else
							{
								UI->ClearMessageToBasicCanvasEventInfoUI(false);
								UI->AddMessageToBasicCanvasEventInfoUI(WrongChoiceLogW);
								Sleep(500);
							}
							break;

						default: // 잘못된 선택
							UI->ClearMessageToBasicCanvasEventInfoUI(false);
							UI->AddMessageToBasicCanvasEventInfoUI(WrongChoiceLogW);
							Sleep(500);
							break;
						}


						if (ItemChoice == EKey::x)
						{
							break;
						}
					}
					break;
				}
				
				

			case EKey::x: // 나가기
				UI->ClearMessageToBasicCanvasEventInfoUI(false);
				UI->AddMessageToBasicCanvasEventInfoUI(GetOutShopLogW);
				return;

			default:
				UI->ClearMessageToBasicCanvasEventInfoUI(false);
				UI->AddMessageToBasicCanvasEventInfoUI(WrongChoiceLogW);
				Sleep(500);
				break;
		}
	}



}

// 품목 출력 함수
void Shop::Display(int index)
{
	std::shared_ptr<UIManager> UI = GameManager::GetInstance().GetUIManager();


	std::string ItemNameLog;
	std::string ItemPriceLog;
	std::string	ItemExplanationLog;

	std::wstring ItemNameLogW;
	std::wstring ItemPriceLogW;
	std::wstring ItemExplanationLogW;

	ItemNameLog = std::to_string(index + 1) + ". 이름: " + ItemsForSale[index]->GetName() + "  가격: " + std::to_string(ItemsForSale[index]->GetPrice()) + "  효과: " + ItemsForSale[index]->GetExplanation() + "   [ <-. 이전 페이지 ] [ z. 구매하기 ]  [ -> 다음 페이지 ] [ x. 뒤로가기 ]";
	//	ItemPriceLog = 
	//	ItemExplanationLog = "  Explanation: " + ItemsForSale[index]->GetExplanation();

	ItemNameLogW = LogicHelper::StringToWString(ItemNameLog);
	ItemPriceLogW = LogicHelper::StringToWString(ItemPriceLog);
	ItemExplanationLogW = LogicHelper::StringToWString(ItemExplanationLog);

	// 이미지 삽입
	UI->ChangeBasicCanvasArtImage(ItemsForSale[index]->GetArtContainer());

	// 로그 출력
	UI->AddMessageToBasicCanvasEventInfoUI(ItemNameLogW);
	//	UI->AddMessageToBasicCanvasEventInfoUI(ItemPriceLogW);
	//	UI->AddMessageToBasicCanvasEventInfoUI(ItemExplanationLogW);
}