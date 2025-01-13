#include <iostream>
#include <algorithm>
#include <random>
#include "Character.h"
#include "Warrior.h"
#include "Mage.h"
#include "Thief.h"
#include "Item.h"


Character::Character() : Level{ 1 }, MaxExp{ 100 }, Exp(0), Damage(0)
{
	InitCharacter();
	RandomizeStats();

/*	Stats.OnStatChanged = [this](EStat statType, int newValue)
	{
			if (OnCharacterChanged)
			{
				OnCharacterChanged(ECharacterEvent::Stat, static_cast<int>(statType));
			}

	};
*/

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
	if (Stats.GetStat(EStat::CurHp) <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 아이템 추가
void Character::AddItem(std::shared_ptr<Item> item)
{
	Inventory.push_back(item);

	// 장비 아이템이면 바로 효과 적용
	if (item->IsConsumable() == true)
	{
		item->Use(this);
	}
	
	if (OnItemChanged)
	{
		OnItemChanged(Inventory);
	}
	
}

// 아이템 사용
void Character::UsePotion(int index)
{
	// 잘못된 인덱스
	if (index < 0 || index >= static_cast<int>(Inventory.size()))
	{
		std::cout << "Invalid index. No item found at index " << index << ".\n";
		return;
	}

	// 아이템 타입 확인 -> Potion인지 아닌지
	std::shared_ptr<Item> item = Inventory[index];

	// 만약 무기라면
	if (item->IsConsumable())
	{
		std::cout << "The item at index " << index << " is not a Potion." << std::endl;
		return;
	}
	else
	{
		item->Use(this);
		Inventory.erase(Inventory.begin() + index);
		
		if (OnItemChanged)
		{
			OnItemChanged(Inventory);
		}
	}

}

int Character::TakeDamage(int damage)
{
	Status Stats = this->GetStatus();
	int Defense =Stats.GetStat(EStat::Defense);

	return std::max((damage - Defense),0);
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
	std::uniform_int_distribution<> distHp(150, 250);
	std::uniform_int_distribution<> distStat(25, 35);

	int Choice = 0;
	while (Choice != 1)
	{
		// 랜덤 스탯을 할당한다.
		int maxHp = distHp(gen);
		int power = distStat(gen);
		int defense = distStat(gen);
		int luck = distStat(gen);

		// 스탯 표시
		std::cout << " 능력치를 설정해주세요!" << std::endl;
		std::cout << "-------------------------------------------------" << std::endl;
		std::cout << "                  PLAYER STATUS                  " << std::endl;
		std::cout << "-------------------------------------------------" << std::endl;
		std::cout << "이  름 : " << Name << std::endl;
		
		std::wcout << "직  업 : " << Jobs->GetJobName() << std::endl;
		std::cout << "레  벨 : " << Level << std::endl;
		std::cout << "경험치 : " << Exp << "/" << MaxExp << std::endl;
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
	float powerWeight = Jobs->GetPowerWeight();
	float defenseWeight = Jobs->GetDefenseWeight();
	float luckWeight = Jobs->GetLuckWeight();
	float damage = Stats.StatToDamage(powerWeight, defenseWeight, luckWeight);
	SetDamage(static_cast<int>(damage));
}

// 레벨업 함수
void Character::LevelUp()
{
	while (Exp >= 100)
	{
		SetLevel(Level + 1);

		// 100이 넘어갔을 경우 초과치를 다음 경험치에 추가합니다.
		Exp = Exp - 100;

		
	}
	int maxHp = Stats.GetStat(EStat::MaxHp);
	int power = Stats.GetStat(EStat::Power);
	int defense = Stats.GetStat(EStat::Defense);
	int luck = Stats.GetStat(EStat::Luck);

	float pWeight = Jobs->GetPowerWeight();
	float dWeight = Jobs->GetDefenseWeight();
	float lWeight = Jobs->GetLuckWeight();

	maxHp += Level * 20;
	power += static_cast<int>(3 * Level * pWeight);
	defense += static_cast<int>(3 * Level * dWeight);
	luck += static_cast<int>(3 * Level * lWeight);

	Stats.SetStat(EStat::MaxHp, maxHp);
	Stats.SetStat(EStat::Power, power);
	Stats.SetStat(EStat::Defense, defense);
	Stats.SetStat(EStat::Luck, luck);

	// 체력 회복
	Stats.SetStat(EStat::CurHp, maxHp);

	// 데미지 재계산
	float damage = Stats.StatToDamage(pWeight, dWeight, lWeight);
	SetDamage(static_cast<int>(damage));

	
}






// Test용 Display 함수
void Character::Display() const
{
	int curHp = Stats.GetStat(EStat::CurHp);
	int maxHp = Stats.GetStat(EStat::MaxHp);
	int power = Stats.GetStat(EStat::Power);
	int defense = Stats.GetStat(EStat::Defense);
	int luck = Stats.GetStat(EStat::Luck);
	int damage = GetDamage();

	std::cout << "여러분의 선택이 캐릭터의 운명을 바꿉니다. 능력치를 설정해주세요!" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "                  PLAYER STATUS                  " << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "이  름 : " << Name << std::endl;
	std::wcout << "직  업 : " << Jobs->GetJobName() << std::endl;
	std::cout << "레  벨 : " << Level << std::endl;
	std::cout << "경험치 : " << Exp << "/" << MaxExp << std::endl;
	std::cout << "체  력 : " << maxHp << "/" << maxHp << std::endl;
	std::cout << "공격력 : " << power << std::endl;
	std::cout << "방어력 : " << defense << std::endl;
	std::cout << "행  운 : " << luck << std::endl;
	std::cout << "데미지 : " << damage << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
}