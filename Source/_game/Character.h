#pragma once
#include <string>


class Character
{
private:
	
	std::string name;
	int level;
	int max_hp;
	int cur_hp;
	int attack_point;
	int ex_point;

	Character();
	

public:
	// ���� ������, = operator, �̵��� �����Ѵ�. (Copy/Move Constructor/Assignment)
	Character(const Character& other) = delete;
	Character& operator= (const Character&) = delete;
	Character(Character&&) = delete;
	Character& operator=(Character&&) = delete;

	static Character& getinstance();

	// Getter �Լ�
	std::string getName() const;
	int getLevel() const;
	int getMaxHp() const;
	int getCurHp() const;
	int getAttackPoint() const;
	int getExp() const;

	// Setter �Լ� (name�� ����)
	int setLevel(int lv);
	int setMaxHp(int mhp);
	int setCurHp(int chp);
	int setAttackPoint(int ap);
	int setExp(int exp);

	

	// ĳ������ ���¸� Ȯ���� �� �ֵ��� �����
	void display() const;
};
