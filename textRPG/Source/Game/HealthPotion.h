#pragma once
#include "Item.h"


class HealthPotion : public Item
{
private:
	std::string Name;
	int HealPoint;


public:
	HealthPotion(std::string name, int healpoint) : Name{ name }, HealPoint{ healpoint },  {}
	std::string GetName() const override;
	void Use(Character* character) override;
	bool IsConsumable() const override { return true; }
};

