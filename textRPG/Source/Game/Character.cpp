#include "Character.h"
#include <iostream>
#include <algorithm>

Character::Character() : level{ 1 }, max_hp{ 200 }, cur_hp(200), attack_point{ 30 }, ex_point{ 0 }
{
	while (true)
	{
		
		std::cout << "생성할 캐릭터의 이름을 입력해주세요: ";
		std::getline(std::cin, name); // 공백 포함 문자열 입력 받기위해 getline 사용

		if (name == "")
		{
			std::cout << "이름을 입력하지 않았습니다. 다시 입력해주세요" << std::endl;
			
		}
		else
		{
			break;
		}
	}
	
}

Character& Character::getinstance() 
{
	static Character instance;
	
	return instance;
}

// Getter 함수
std::string Character::getName() const { return name; }
int Character::getLevel() const { return level; }
int Character::getMaxHp() const { return max_hp; }
int Character::getCurHp() const { return cur_hp; }
int Character::getAttackPoint() const { return attack_point; }
int Character::getExp() const { return ex_point; }

// Setter 함수
void Character::setLevel(int lv)
{
	// Level최소 1, 최대 10
	level = std::max(1, std::min(lv, 10));
	
}
void Character::setMaxHp(int mhp)
{
	max_hp = mhp;
}
void Character::setCurHp(int chp)
{
	cur_hp = std::max(0, std::min(chp, max_hp));
}
void Character::setAttackPoint(int ap)
{
	attack_point = ap;
}
void Character::setExp(int exp)
{
	ex_point = exp;
}






void Character::display() const
{
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "                  PLAYER STATUS                  " << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "이  름 : " << name << std::endl;
	std::cout << "레  벨 : " << level << std::endl;
	std::cout << "경험치 : " << ex_point << "/" << "100" << std::endl;
	std::cout << "체  력 : " << cur_hp << "/" << max_hp << std::endl;
	std::cout << "공격력 : " << attack_point << std::endl;
}