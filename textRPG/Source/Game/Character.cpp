#include "Character.h"
#include <iostream>
#include <algorithm>

Character::Character() : level{ 1 }, max_hp{ 200 }, cur_hp(200), attack_point{ 30 }, ex_point{ 0 }
{
	while (true)
	{
		
		std::cout << "������ ĳ������ �̸��� �Է����ּ���: ";
		std::getline(std::cin, name); // ���� ���� ���ڿ� �Է� �ޱ����� getline ���

		if (name == "")
		{
			std::cout << "�̸��� �Է����� �ʾҽ��ϴ�. �ٽ� �Է����ּ���" << std::endl;
			
		}
		else
		{
			break;
		}
	}
	
}

Character& Character::getinstance() // ���⿡ static Ű���带 ���� �ȵ�
{
	static Character instance; // ��� ���Ͽ� static ������ ������ ��� ��� cpp ���Ͽ��� �����ϴ� �ߺ� ���� �߻�
	
	return instance;
}

// Getter �Լ� ����
std::string Character::getName() const { return name; }
int Character::getLevel() const { return level; }
int Character::getMaxHp() const { return max_hp; }
int Character::getCurHp() const { return cur_hp; }
int Character::getAttackPoint() const { return attack_point; }
int Character::getExp() const { return ex_point; }

// Setter �Լ� ����
void Character::setLevel(int lv)
{
	// Level�� 1�̻� 10���Ϸ� ����
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

// Observer ���� Ŭ���� �����??




void Character::display() const
{
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "                  PLAYER STATUS                  " << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "��  �� : " << name << std::endl;
	std::cout << "��  �� : " << level << std::endl;
	std::cout << "ü  �� : " << cur_hp << "/" << max_hp << std::endl;
	std::cout << "���ݷ� : " << attack_point << std::endl;
}