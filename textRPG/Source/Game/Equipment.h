#pragma once
#include "IItem.h"


class Equipment : public IItem
{
private:
	std::string Name; // 이름
	EStat StatType;   // 올릴 스탯
	int AffectPoint;  // 올릴 포인트
	int Price; // 가격
	std::string Explanation; // 설명
	

public:
	
	std::string EStatToString(EStat stat) {
		switch (stat) {
		case EStat::Power: return "Power";
		case EStat::Defense: return "Defense";
		case EStat::Luck: return "Luck";
		default: return "Unknown";
		}
	}

	
	Equipment(std::string name, EStat stat, int point, int price) : Name{ name }, StatType { stat }, AffectPoint{ point }, Price{ price } 
	{
		Explanation = EStatToString(stat) + ": + " + std::to_string(point);
	}

	std::string GetName() const override;

	int GetPrice() const override;

	std::string GetExplanation() const override;

	void Use(Character& character) override;

	void UnUse(Character& character) override;
	
	bool IsConsumable() const override { return false; }






};
