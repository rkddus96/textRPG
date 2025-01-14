#include <iostream>
#include <algorithm>
#include <random>
#include <memory>
#include "Character.h"
#include "Warrior.h"
#include "Mage.h"
#include "Thief.h"
#include "IItem.h"
#include "Managers/UIManager.h"
#include "LogicHelper.h"
#include "Managers/GameManager.h"

Character::Character() : Level{ 1 }, MaxExp{ 100 }, Exp(0)
{
	InitCharacter();
	RandomizeStats();

	Inventory.clear(); //Item 추가 시 추가
	
}

Character& Character::GetInstance() 
{
	static Character instance;
	
	return instance;
}

void Character::SetExp(int exp)
{
	Exp = std::max(0, exp);
	if (OnCharacterChanged)
	{
		OnCharacterChanged(ECharacterEvent::Exp, Exp);
	}
}

void Character::RaiseExp(int exp)
{
	Exp += exp;
	if (OnCharacterChanged)
	{
		OnCharacterChanged(ECharacterEvent::Exp, Exp);
	}
}

void Character::SetLevel(int level)
{
	Level = std::max(1, std::min(level, 10));
	if (OnCharacterChanged)
	{
		OnCharacterChanged(ECharacterEvent::Level, Level);
	}
}

void Character::SetGold(int gold)
{
	Gold = gold;
	if (OnCharacterChanged)
	{
		OnCharacterChanged(ECharacterEvent::Gold, Gold);
	}
}

void Character::RaiseGold(int gold)
{
	Gold += gold;
	if (OnCharacterChanged)
	{
		OnCharacterChanged(ECharacterEvent::Gold, Gold);
	}
}

// 생존 여부 반환 함수
bool Character::IsDead()
{
	return (Stats.GetStat(EStat::CurHp) <= 0);

}

// 아이템 추가
void Character::AddItem(std::shared_ptr<IItem> item)
{
	Inventory.push_back(item);

	// 장비 아이템이면 바로 효과 적용
	if (item->IsConsumable() == false)
	{
		item->Use(*this);
	}
	
	if (OnItemChanged)
	{
		OnItemChanged(Inventory);
	}
	
}

// 아이템 사용
void Character::UsePotion()
{
	//UI 초기화
	std::shared_ptr<UIManager> UI = GameManager::GetInstance().GetUIManager();
	
	std::string CannotUsePotionLog;
	std::wstring CannotUsePotionLogW;
	CannotUsePotionLog = "인벤토리 내부에 포션이 없습니다.";

	CannotUsePotionLogW = LogicHelper::StringToWString(CannotUsePotionLog);
	

	for (int index = 0; index < Inventory.size(); index++)
	{
		if (Inventory[index]->IsConsumable())
		{
			Inventory[index]->Use(*this);
			Inventory.erase(Inventory.begin() + index);
			if (OnItemChanged)
			{
				OnItemChanged(Inventory);
			}
			break;
		}
	}
	UI->AddMessageToBasicCanvasEventInfoUI(CannotUsePotionLogW);
	
}

int Character::TakeDamage(int rawdamage)
{
	Status& Stats = this->GetStatus();
	int Defense =Stats.GetStat(EStat::Defense);

	int damage = std::max((rawdamage - Defense), 0);
	int Hp = Stats.GetStat(EStat::CurHp) - damage;
	Stats.SetStat(EStat::CurHp, Hp);

	
	return damage;
}

// 캐릭터 생성 함수
void Character::InitCharacter()
{
	//1. 이름 설정
	while (true)
	{
		std::cout << "생성할 캐릭터의 이름을 입력해주세요: ";
		std::getline(std::cin, Name);

		if (Name.empty())
		{
			std::cout << "이름을 입력하지 않았습니다. 다시 입력해주세요" << std::endl;
		}
		else
		{
			break;
		}
	}

	//2. 직업 선택
	while (true)
	{
		std::cout << "직업을 선택해주세요." << std::endl;
		std::cout << "1. Warrior: Power를 주요 능력으로 하며, 맨 앞에서 전투를 수행하는 용맹한 전사입니다." << std::endl;
		std::cout << "2. Mage: Defense를 주요 능력으로 하며, 적의 공격을 무력화시켜 몸을 지키는 돕는 마법의 대가입니다." << std::endl;
		std::cout << "3. Thief: Luck을 주요 능력으로 하며, 운과 기술을 이용해 전장에서 살아남는 치명적인 전략가입니다. " << std::endl;
		int JobChoice = 0;
		std::cin >> JobChoice;

		switch (JobChoice)
		{
		case 1:
			Jobs = std::make_shared<Warrior>();
			break;
		
		case 2:
			Jobs = std::make_shared<Mage>();
			break;

		case 3:
			Jobs = std::make_shared<Thief>();
			break;
		
		default:
			std::cout << "잘못된 입력입니다. 다시 시도해주세요." << std::endl;
		}

		if (OnCharacterChanged)
		{
			OnCharacterChanged(ECharacterEvent::Job, JobChoice);
		}

		if (JobChoice == 1 || JobChoice == 2 || JobChoice == 3)
		{
			break;
		}
	}
}

// 스탯 설정 함수
void Character::RandomizeStats()
{
	// 시드 설정 및 난수 초기화
	std::random_device rd;
	std::mt19937 gen(rd());

	// 범위, 분포 설정
	std::uniform_int_distribution<> distHp(100, 130);
	std::uniform_int_distribution<> distPower(10, 15);
	std::uniform_int_distribution<> distDefense(3, 5);
	std::uniform_int_distribution<> distLuck(0, 10);

	std::cout << "이  름 : " << Name << std::endl;
	std::cout << "레  벨 : " << Level << std::endl;
	std::wcout <<"직  업 : " << Jobs->GetJobName() << std::endl;

	int Choice = 0;
	while (Choice != 1)
	{
		// 랜덤 스탯을 할당한다.
		int maxHp = distHp(gen);
		int power = distPower(gen);
		int defense = distDefense(gen);
		int luck = distLuck(gen);

		// 스탯 표시
		std::cout << " 능력치를 설정해주세요!" << std::endl;
		std::cout << "-------------------------------------------------" << std::endl;
		std::cout << "                  PLAYER STATUS                  " << std::endl;
		std::cout << "-------------------------------------------------" << std::endl;
		std::cout << "체  력 : " << maxHp << "/" << maxHp << std::endl;
		std::cout << "공격력 : " << power << std::endl;
		std::cout << "방어력 : " << defense << std::endl;
		std::cout << "행  운 : " << luck << std::endl;
		std::cout << "-------------------------------------------------" << std::endl;
		std::cout << "능력치를 확정하시겠습니까?" << std::endl;
		std::cout << "1. 결정" << std::endl;
		std::cout << "2. 재설정" << std::endl;
		std::cin >> Choice;

		// cin 에러 예외 처리
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			Choice = 0;
		}

		switch (Choice)
		{
		case 1:
			// Stats에 저장, Damage 계산
			Stats.SetStat(EStat::MaxHp, maxHp);
			Stats.SetStat(EStat::CurHp, maxHp);
			Stats.SetStat(EStat::Power, power);
			Stats.SetStat(EStat::Defense, defense);
			Stats.SetStat(EStat::Luck, luck);

			std::cout << "능력치가 확정되었습니다." << std::endl;
			break;

		case 2:
			std::cout << "스탯을 재설정합니다." << std::endl;
			break;

		default:
			std::cout << "잘못된 입력입니다. 다시 입력해주세요." << std::endl;
			break;
		}
	}
	// Damage 계산
	int powerWeight = Jobs->GetPowerWeight();
	int defenseWeight = Jobs->GetDefenseWeight();
	int luckWeight = Jobs->GetLuckWeight();
}

// 레벨업 함수
void Character::LevelUp()
{
	while (Exp >= MaxExp)
	{
		SetLevel(Level + 1);

		// 100이 넘어갔을 경우 초과치를 다음 경험치에 추가합니다.
		Exp = Exp - MaxExp;
		MaxExp += 50;

		
	}
	int maxHp = Stats.GetStat(EStat::MaxHp);
	int power = Stats.GetStat(EStat::Power);
	int defense = Stats.GetStat(EStat::Defense);
	int luck = Stats.GetStat(EStat::Luck);

	int pWeight = Jobs->GetPowerWeight();
	int dWeight = Jobs->GetDefenseWeight();
	int lWeight = Jobs->GetLuckWeight();

	maxHp += 20;
	power += pWeight;
	defense += dWeight;
	luck += lWeight;

	Stats.SetStat(EStat::MaxHp, maxHp);
	Stats.SetStat(EStat::Power, power);
	Stats.SetStat(EStat::Defense, defense);
	Stats.SetStat(EStat::Luck, luck);

	// 체력 회복
	Stats.SetStat(EStat::CurHp, maxHp);


	
}

// DisplayInventory 함수
void Character::DisplayInventory()
{
	std::shared_ptr<UIManager> UI = GameManager::GetInstance().GetUIManager();


	std::string ItemNameLog;
	std::string ItemPriceLog;
	std::string	ItemExplanationLog;

	std::wstring ItemNameLogW;
	std::wstring ItemPriceLogW;
	std::wstring ItemExplanationLogW;




	for (int i = 0; i < Inventory.size(); i++)
	{
		ItemNameLog = std::to_string(i + 1) + ". Name: " + Inventory[i]->GetName();
		ItemPriceLog = "  Price: " + std::to_string(Inventory[i]->GetPrice());
		ItemExplanationLog = "  Explanation: " + Inventory[i]->GetExplanation();

		ItemNameLogW = LogicHelper::StringToWString(ItemNameLog);
		ItemPriceLogW = LogicHelper::StringToWString(ItemPriceLog);
		ItemExplanationLogW = LogicHelper::StringToWString(ItemExplanationLog);


		UI->AddMessageToBasicCanvasEventInfoUI(ItemNameLogW);
		UI->AddMessageToBasicCanvasEventInfoUI(ItemPriceLogW);
		UI->AddMessageToBasicCanvasEventInfoUI(ItemExplanationLogW);
	}
}


void Character::Notify()
{
	SetExp(GetExp());
	SetLevel(GetLevel());
	SetGold(GetGold());
	
	Status& Stats = GetStatus();
	Stats.SetStat(EStat::CurHp, Stats.GetStat(EStat::CurHp));
	Stats.SetStat(EStat::Power, Stats.GetStat(EStat::Power));
	Stats.SetStat(EStat::Defense, Stats.GetStat(EStat::Defense));
	Stats.SetStat(EStat::Luck, Stats.GetStat(EStat::Luck));
	Stats.SetStat(EStat::MaxHp, Stats.GetStat(EStat::MaxHp));
}


