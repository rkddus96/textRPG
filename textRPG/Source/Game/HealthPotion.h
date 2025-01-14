#pragma once
#include "IItem.h"

class HealthPotion : public IItem
{
private:
	std::string Name;
	int Price;
	std::string Explanation;


public:
	HealthPotion(std::string name, int price) : Name{ name }, Price{ price } 
	{
		Explanation = "hp: + 50%";
	}
	std::string GetName() const override;
	int GetPrice() const override;
	void Use(Character& character) override;
	void UnUse(Character& character) override;
	std::string GetExplanation() const override;
	bool IsConsumable() const override { return true; }

};

