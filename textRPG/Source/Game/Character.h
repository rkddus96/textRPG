#pragma once
#include <string>
#include <memory>
#include <vector>
#include <functional> // 콜백함수를 위해 추가

#include "Status.h"
#include "IJob.h"
#include "Managers/UIManager.h"
#include "LogicHelper.h"
#include "Managers/GameManager.h"
#include "InputReceiver.h"
#include "ConstantContainer.h"
#include "Warrior.h"
#include "Mage.h"
#include "Thief.h"


class IItem;// Item 구현 시 추가

enum class ECharacterEvent
{
	Level,
	Exp,
	Inventory,
	Stat,
	Job,
	Gold,
	Item // 아이템 이름, 인덱스 이름, (아이템 설명)
};


class Character
{	
protected:
	std::shared_ptr<UIManager> 	UI = GameManager::GetInstance().GetUIManager();

private:
	
	std::string Name;
	int Level;
	int MaxExp;
	int Exp;
	int Gold;

	Status Stats;
	std::shared_ptr<IJob> Jobs;
	std::vector<std::shared_ptr<IItem>> Inventory; 

	// 직업을 저장할 vector
	std::vector<std::shared_ptr<IJob>> JobList;


	Character();
	

public:

	std::function<void(ECharacterEvent, int)> OnCharacterChanged;
	// 아이템 설명 생겼을 때 추가
	std::function<void(const std::vector<std::shared_ptr<IItem>>&)> OnItemChanged;


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
	int GetMaxExp() const { return MaxExp; }
	int GetGold() const { return Gold; }
	Status& GetStatus() { return Stats; }
	std::shared_ptr<IJob> GetJob() const { return Jobs; }
	std::vector<std::shared_ptr<IItem>>& GetInventory() { return Inventory; }

	// Setter 함수
	void SetExp(int exp);
	void SetLevel(int level);
	void SetGold(int gold);
	void SetJob(std::shared_ptr<IJob> jobs);

	// Raise 함수 : 기존에 매개변수로 받은 것 추가
	void RaiseGold(int gold);
	void RaiseExp(int exp);
	
	
	// 캐릭터 생성 함수
	void InitCharacter();
	void RandomizeStats();

	// 레벨업 함수
	void LevelUp();

	// 캐릭터 생존 여부
	bool IsDead();

	// 데미집 입는 함수
	int TakeDamage(int rawdamage);
	
	// 인벤토리 추가
	void AddItem(std::shared_ptr<IItem> item);

	// 아이템 사용
	void UsePotion();

	// 인벤토리 출력
	
	void DisplayInventory(int index);

	void Notify();

};
