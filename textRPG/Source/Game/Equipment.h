#pragma once
#include "IItem.h"

class Equipment : public IItem
{
private:
	std::string Name; // 이름
	EStat StatType;   // 올릴 스탯
	int AffectPoint;  // 올릴 포인트
	

public:
	Equipment(EStat stat, int point) : StatType{ stat }, AffectPoint{ point } {}

	std::string GetName() const override;

	void Use(Character* character) override;

	bool IsConsumable() const override { return false; }

};
