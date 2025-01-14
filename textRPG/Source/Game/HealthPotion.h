#pragma once
#include "IItem.h"


class HealthPotion : public IItem
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

