#pragma once
#include <unordered_map>
#include <functional>

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

	std::function<void(EStat, int)> OnStatChanged;

	// 특정 스탯 Getter, Setter
	int GetStat(EStat statType) const;
	void SetStat(EStat statType, int value);

	
};