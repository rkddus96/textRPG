#include "Character.h"
#include <iostream>
#include <algorithm>

Character::Character() : Level{ 1 }, MaxHp{ 200 }, CurHp(200), AttackPoint{ 30 }, ExPoint{ 0 }
{
	while (true)
	{
		
		std::cout << "생성할 캐릭터의 이름을 입력해주세요: ";
		std::getline(std::cin, Name); // 공백 포함 문자열 입력 받기위해 getline 사용

		if (Name == "")
		{
			std::cout << "이름을 입력하지 않았습니다. 다시 입력해주세요" << std::endl;
			
		}
		else
		{
			break;
		}
	}
	
}

Character& Character::GetInstance() 
{
	static Character instance;
	
	return instance;
}

// Getter 함수
std::string Character::GetName() const { return Name; }
int Character::GetLevel() const { return Level; }
int Character::GetMaxHp() const { return MaxHp; }
int Character::GetCurHp() const { return CurHp; }
int Character::GetAttackPoint() const { return AttackPoint; }
int Character::GetExp() const { return ExPoint; }

// Setter 함수
void Character::SetLevel(int lv)
{
	// Level최소 1, 최대 10
	Level = std::max(1, std::min(lv, 10));
	
}
void Character::SetMaxHp(int mhp)
{
	MaxHp = mhp;
}
void Character::SetCurHp(int chp)
{
	CurHp = std::max(0, std::min(chp, MaxHp));
}
void Character::SetAttackPoint(int ap)
{
	AttackPoint = ap;
}
void Character::SetExp(int exp)
{
	ExPoint = exp;
}





// Test용
void Character::display() const
{
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "                  PLAYER STATUS                  " << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "이  름 : " << Name << std::endl;
	std::cout << "레  벨 : " << Level << std::endl;
	std::cout << "경험치 : " << ExPoint << "/" << "100" << std::endl;
	std::cout << "체  력 : " << CurHp << "/" << MaxHp << std::endl;
	std::cout << "공격력 : " << AttackPoint << std::endl;
}