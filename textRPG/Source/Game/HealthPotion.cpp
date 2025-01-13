#include "HealthPotion.h"

std::string HealthPotion::GetName() const
{
	return Name;
}

void HealthPotion::Use(Character* character)
{
	Status Stats = character->GetStatus();
	
	//Character HP
	int Hp = Stats.GetStat(EStat::CurHp);
	int MaxHp = Stats.GetStat(EStat::MaxHp);
	Hp = std::min(Hp + HealPoint, MaxHp);
	Stats.SetStat(EStat::CurHp, Hp);
}
