#pragma once

#include <iostream>
#include <vector>

// 알파벳 순으로 정렬 필수
enum class EArtList
{
	Armor,
	Axe,
	Axe2,
	Axe3,
	Boss,
	Boss2,
	Castle1,
	Castle2,
	CastleSmall,
	Church,
	Desert,
	Devil,
	FakeBoss,
	Goblin,
	Helmet,
	Heroine,
	Landscape,
	MainCharacter,
	Merchant,
	MerchantTwo,
	Mountain1,
	Mountain2,
	Mountain3,
	Mountain4,
	Mountain5,
	Necklace,
	Orc,
	Potion,
	ShortSword,
	Slime,
	Store,
	StoreLarge,
	Sword,
	Sword2,
	Test,
	Test2,
	Title,
	Village1,
	Village2,
	Wand,
	Waterfall,
	Witch

};

struct FASCIIArtContainer
{
public:

	int GetWidth() const
	{
		return (int)ArtLines[0].size();
	}

	int GetHeight() const
	{
		return (int)ArtLines.size();
	}

	std::wstring ArtName;
	std::vector<std::wstring> ArtLines;
};

class AssetHandler
{
public:

	AssetHandler();

	AssetHandler(const AssetHandler&) = delete;
	AssetHandler& operator=(const AssetHandler&) = delete;
	AssetHandler(AssetHandler&&) = delete;
	AssetHandler& operator=(AssetHandler&&) = delete;

	~AssetHandler();

	const FASCIIArtContainer& GetASCIIArtContainer(EArtList ArtList) const
	{
		return ArtContainers[(int)ArtList];
	}

private:

	void ReadAllArts();

	void ReadArt(const std::wstring& Filename);

	std::vector<FASCIIArtContainer> ArtContainers;

	friend class GameManager;
};