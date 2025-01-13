#pragma once
#include "Item.h"


class HealthPotion : public Item
{
private:
	std::string Name;
	int HealPoint;
	bool IsEquipment


public:
	HealthPotion(std::string name, int healpoint) : Name{ name }, HealPoint{ healpoint }, IsEquiopment{ false } {}
	std::string GetName() const override;
	void Use(Character* character) override;
	void GetState() const override { return IsEquipment; }
};

