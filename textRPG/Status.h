#pragma once
#include <unordered_map>


enum class EStat
{
	MaxHp,
	CurHp,
	Power,
	Luck,
	Defense
};



class Status
{
private:
	std::unordered_map<EStat, int> stats;

public:
	Status();

	// 특정 스탯 Getter, Setter
	int GetStat(EStat statType) const;
	void SetStat(EStat statType, int value);

	
	// 스탯 -> 데미지
	float StatToDamage(float powerWeight, float defenseWeight, float luckWeight);
};