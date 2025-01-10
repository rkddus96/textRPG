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
	// 복사 생성자, = operator, 이동을 금지한다. (Copy/Move Constructor/Assignment)
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

	// Setter 함수 (name만 제외)
	int setLevel(int lv);
	int setMaxHp(int mhp);
	int setCurHp(int chp);
	int setAttackPoint(int ap);
	int setExp(int exp);

	

	// 캐릭터의 상태를 확인할 수 있도록 만들기
	void display() const;
};
