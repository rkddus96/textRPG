#include "Equipment.h"

std::string Equipment::GetName() const
{
	return Name;
}

void Equipment::Use(Character* character)
{
	Status Stats = character->GetStatus();

	int StatPoint = Stats.GetStat(StatType);
	StatPoint = StatPoint + AffectPoint;
	Stats.SetStat(StatType, StatPoint);
}

