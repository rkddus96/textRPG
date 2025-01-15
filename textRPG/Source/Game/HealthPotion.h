#pragma once
#include "IItem.h"

class HealthPotion : public IItem
{
private:
	std::string Name;
	int Price;
	std::string Explanation;
	const FASCIIArtContainer& ArtContainer; //아이템의 이미지


public:
	HealthPotion(std::string name, int price, const FASCIIArtContainer& artContainer) : Name{ name }, Price{ price } , ArtContainer {artContainer}
	{
		Explanation = "hp: + 50%";
	}
	std::string GetName() const override;

	int GetPrice() const override;
	
	virtual const FASCIIArtContainer& GetArtContainer() const override;

	void Use(Character& character) override;
	
	void UnUse(Character& character) override;
	
	std::string GetExplanation() const override;
	
	bool IsConsumable() const override { return true; }

};

