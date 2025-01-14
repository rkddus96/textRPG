#pragma once
#include "IItem.h"


class Equipment : public IItem
{
private:
	std::string Name; // 이름
	std::vector<EStat> StatTypes;   // 올릴 스탯
	std::vector<int> AffectPoints;  // 올릴 포인트
	int Price; // 가격
	std::string Explanation; // 설명
	const FASCIIArtContainer& ArtContainer; // 아이템의 이미지

public:
	
	std::string EStatToString(EStat stat) {
		switch (stat) {
		case EStat::Power: return "Power";
		case EStat::Defense: return "Defense";
		case EStat::Luck: return "Luck";
		default: return "Unknown";
		}
	}

	
	Equipment(std::string name,
			  std::vector<EStat> statTypes,
			  std::vector<int> affectPoints, int price,
			  const FASCIIArtContainer& artContainer)
			  : Name{ name }, StatTypes { statTypes }, AffectPoints{ affectPoints }, Price{ price }, ArtContainer{artContainer}
	{
		Explanation = "";
		for (int i = 0; i < StatTypes.size(); i++)
		{
			if (!Explanation.empty())
			{
				Explanation += ",";
			}
			Explanation += EStatToString(StatTypes[i]) + ": + " + std::to_string(AffectPoints[i]);
		}
	}

	std::string GetName() const override;

	int GetPrice() const override;

	std::string GetExplanation() const override;

	virtual const FASCIIArtContainer& GetArtContainer() const override;

	bool IsUsed(Character& character) override;

	void UnUse(Character& character) override;
	
	bool IsConsumable() const override { return false; }






};
