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
	// 복사, 이동 제거
	Character(const Character& other) = delete;
	Character& operator= (const Character&) = delete;
	Character(Character&&) = delete;
	Character& operator=(Character&&) = delete;

	static Character& getinstance();

	// Getter 함수
	std::string getName() const;
	int getLevel() const;
	int getMaxHp() const;
	int getCurHp() const;
	int getAttackPoint() const;
	int getExp() const;

	// Setter 함수
	void setLevel(int lv);
	void setMaxHp(int mhp);
	void setCurHp(int chp);
	void setAttackPoint(int ap);
	void setExp(int exp);

	

	
	void display() const;
};
