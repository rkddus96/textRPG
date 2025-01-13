#pragma once
#include <string>
#include <memory>
#include <vector>
#include <functional> // 콜백함수를 위해 추가
// #include "Item.h" // Item 구현 시 추가
#include "Status.h"
#include "Job.h"

enum class ECharacterEvent
{
	Level,
	Exp,
	Inventory,
	Stat,
	Job
};


class Character
{
private:
	
	std::string Name;
	int Level;
	int MaxExp;
	int Exp;
	int Damage;

	Status Stats;
	std::shared_ptr<Job> Jobs;

//	std::vector<std::shared_ptr<Item>> Inventory; // Item 구현 시 추가

	std::function<void(ECharacterEvent, int)> OnCharacterChanged;

	Character();
	

public:
	// 복사, 이동 제거
	Character(const Character& other) = delete;
	Character& operator= (const Character&) = delete;
	Character(Character&&) = delete;
	Character& operator=(Character&&) = delete;

	// 싱글톤 인스턴스
	static Character& GetInstance();

	// Getter 함수
	const std::string& GetName() const { return Name; }
	int GetLevel() const { return Level; }
	int GetExp() const { return Exp; }
	int GetDamage() const { return Damage; }
	int GetMaxExp() const { return MaxExp; }
	Status& GetStatus() { return Stats; }
	std::shared_ptr<Job> GetJob() const { return Jobs; }

	// Setter 함수
	void SetExp(int exp);
	void SetDamage(int damage) { Damage = damage; }
	void SetLevel(int level);
	
	
	// 캐릭터 생성 함수
	void InitCharacter();
	void RandomizeStats();

	// 레벨업 함수
	void LevelUp();
	

	
	void Display() const;
};
