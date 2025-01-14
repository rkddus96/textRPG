#pragma once
#include "IItem.h"


class HealthPotion : public IItem
{
private:
	std::string Name;
	


public:
	HealthPotion(std::string name) : Name{ name }   {}
	std::string GetName() const override;
	void Use(Character* character) override;
	bool IsConsumable() const override { return true; }
};

