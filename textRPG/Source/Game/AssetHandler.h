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
	FakeBoss,
	Helmet,
	Heroine,
	MainCharacter,
	Necklace,
	Orc,
	Potion,
	ShortSword,
	Slime,
	Store,
	Sword,
	Sword2,
	Test,
	Test2,
	Title,
	Wand,
	Witch

};

struct FASKIIArtContainer
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

	const FASKIIArtContainer& GetASKIIArtContainer(EArtList ArtList) const
	{
		return ArtContainers[(int)ArtList];
	}

private:

	void ReadAllArts();

	void ReadArt(const std::wstring& Filename);

	int ConsoleWidth = 0;
	int ConsoleHeight = 0;

	std::vector<FASKIIArtContainer> ArtContainers;

	friend class GameManager;
};