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

	for (int i = 0; i < StatTypes.size(); i++)
	{
		int StatPoint = Stats.GetStat(StatTypes[i]);
		Stats.SetStat(StatTypes[i], StatPoint + AffectPoints[i]);
	}
}

void Equipment::UnUse(Character& character)
{
	Status Stats = character.GetStatus();

	for (int i = 0; i < StatTypes.size(); i++)
	{
		int StatPoint = Stats.GetStat(StatTypes[i]);
		Stats.SetStat(StatTypes[i], StatPoint - AffectPoints[i]);
	}
}
