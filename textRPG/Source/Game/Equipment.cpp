#include "Equipment.h"

std::string Equipment::GetName() const 
{
	return Name;
}

int Equipment::GetPrice() const
{
	return Price;
}

std::string Equipment::GetExplanation() const
{
	return Explanation;
}

void Equipment::Use(Character& character)
{
	Status Stats = character.GetStatus();

	int StatPoint = Stats.GetStat(StatType);
	StatPoint = StatPoint + AffectPoint;
	Stats.SetStat(StatType, StatPoint);
}

void Equipment::UnUse(Character& character)
{
	Status Stats = character.GetStatus();

	int StatPoint = Stats.GetStat(StatType);
	StatPoint = StatPoint - AffectPoint;
	Stats.SetStat(StatType, StatPoint);
}
