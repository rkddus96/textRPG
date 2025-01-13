#include <iostream>
#include <algorithm>
#include <random>
#include "Character.h"
#include "Warrior.h"
#include "Mage.h"
#include "Thief.h"
#include "./Managers/GameManager.h"


Character::Character() : Level{ 1 }, MaxExp{ 100 }, Exp(0), Damage(0)
{
	CharacterImage = GameManager::GetInstance().GetAssetHandler()->GetASKIIArtContainer(EArtList::MainCharacter);

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

//	Inventory.clear(); //Item 추가 시 추가
	
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


// 생존 여부 반환 함수
bool Character::IsDead() const
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

int Character::TakeDamage(int damage) const
{
	int Defense = Stats.GetStat(EStat::Defense);
	int GetDamage = damage - Defense;

	return GetDamage;
	
}

// 이미지 생성 함수



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
		std::cout << "직업을 선택해주세요.(1. Warrior / 2. Mage / 3. Theif)" << std::endl;
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