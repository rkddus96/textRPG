#pragma once

#include <iostream>
#include <vector>

enum class EArtList
{
	Test,
	Test2
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

	std::vector<std::wstring> ArtLines;
};

class AssetHandler
{
public:

	AssetHandler();

	~AssetHandler();

	const FASKIIArtContainer& GetASKIIArtContainer(EArtList ArtList) const
	{
		return ArtContainers[(int)ArtList];
	}

private:

	void ReadArt(const std::wstring& Filename);

	int ConsoleWidth = 0;
	int ConsoleHeight = 0;

	std::vector<FASKIIArtContainer> ArtContainers;

};