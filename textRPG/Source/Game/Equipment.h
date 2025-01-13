#pragma once
#include "Item.h"

class Equipment : public Item
{
private:
	std::string Name; // 이름
	EStat StatType;   // 올릴 스탯
	int AffectPoint;  // 올릴 포인트
	bool IsEquipment;

public:
	Equipment(EStat stat, int point) : StatType{ stat }, AffectPoint{ point }, IsEquipment{true} {}

	std::string GetName() const override;

	void Use(Character* character) override;

	bool GetState() const override { return IsEquipment;  }

};
