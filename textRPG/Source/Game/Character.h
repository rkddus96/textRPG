#pragma once
#include <string>


class Character
{
private:
	
	std::string Name;
	int Level;
	int MaxHp;
	int CurHp;
	int Power;
	int Exp;

	Character();
	

public:
	// 복사, 이동 제거
	Character(const Character& other) = delete;
	Character& operator= (const Character&) = delete;
	Character(Character&&) = delete;
	Character& operator=(Character&&) = delete;

	static Character& GetInstance();

	// Getter 함수
	std::string GetName() const;
	int GetLevel() const;
	int GetMaxHp() const;
	int GetCurHp() const;
	int GetPower() const;
	int GetExp() const;

	// Setter 함수
	void SetLevel(int lv);
	void SetMaxHp(int mhp);
	void SetCurHp(int chp);
	void SetPower(int ap);
	void SetExp(int exp);

	

	
	void display() const;
};
