#include "HealthPotion.h"
#include <algorithm>

std::string HealthPotion::GetName() const
{
	return Name;
}

int HealthPotion::GetPrice() const
{
	return Price;
}

std::string HealthPotion::GetExplanation() const
{
	return Explanation;
}

const FASCIIArtContainer& HealthPotion::GetArtContainer() const
{
	return ArtContainer;
}


bool HealthPotion::IsUsed(Character& character)
{
	Status& Stats = character.GetStatus();
	
	//Character HP
	int Hp = Stats.GetStat(EStat::CurHp);
	int MaxHp = Stats.GetStat(EStat::MaxHp);
	Hp = std::min(Hp + MaxHp/2, MaxHp);
	Stats.SetStat(EStat::CurHp, Hp);

	return true;
}

void HealthPotion::UnUse(Character& character)
{
	return;
}

