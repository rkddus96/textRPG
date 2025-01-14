#include "TileMap.h"

#include "LogicHelper.h"

TileMap::TileMap(int Width, int Height)
	:TileGrid(Height, std::vector(Width, ETile::Blank)), TileArtGrid(Height, std::vector(Width, EArtList::Axe)), Width(Width), Height(Height)
{
	GenerateTestMap();
}

std::pair<int, int> TileMap::GetCurrentPosition() const
{
	return CurrentPlayerPosition;
}

EArtList TileMap::GetCurrentTileArt() const
{
	return TileArtGrid[CurrentPlayerPosition.first][CurrentPlayerPosition.second];
}

void TileMap::Move(int NextX, int NextY)
{
	if (!CanTraverse(NextX, NextY))
	{
		// 필요할 경우 로깅 혹은 exeception 발생
		return;
	}
	CurrentPlayerPosition = {NextX, NextY};

	// 맵이 변경된 것을 알림
	if (OnMapChanged)
	{
		OnMapChanged(GetCurretnMapData());
	}
}

FAvailableDirection TileMap::GetAvailableDirection()
{
	FAvailableDirection Direction;

	int X = CurrentPlayerPosition.first;
	int Y = CurrentPlayerPosition.second;

	Direction.bLeft = CanTraverse(X - 1, Y);
	Direction.bUp = CanTraverse(X, Y - 1);
	Direction.bRight = CanTraverse(X + 1, Y);
	Direction.bDown = CanTraverse(X, Y + 1);

	return Direction;
}

bool TileMap::CanTraverse(int X, int Y) const
{
	return (X >= 0 && X < Height && Y >= 0 && Y < Width) && TileGrid[X][Y] != ETile::Block;
}

std::vector<std::vector<ETile>> TileMap::GetCurretnMapData()
{
	std::vector<std::vector<ETile>> CurrentMap = TileGrid;
	CurrentMap[CurrentPlayerPosition.first][CurrentPlayerPosition.second] = ETile::Character;

	return CurrentMap;
}

void TileMap::GenerateRandomMap()
{
	int maxTileType = static_cast<int>(ETile::Count) - 1;

	for (int row = 0; row < Height; row++) {
		for(int col = 0; col < Width; col++) {
			TileGrid[row][col] = static_cast<ETile>(LogicHelper::GetRandomNumber(0, maxTileType));
		}
	}
}

void TileMap::GenerateTestMap()
{
	if (Width <= 0 || Height <= 0) {
		return;
	}

	// 좌상단이 마을, 우상단이 마을2, 우하단이 마왕성
	// To-Do : 초기화 과정에서 Tile Type과 Art Type을 한 번에 설정할 수 있도록 하는 기능 구현
	TileGrid[0][0] = ETile::Village1;
	TileArtGrid[0][0] = EArtList::Test;
	TileGrid[Height - 1][0] = ETile::Village2;
	TileArtGrid[Height - 1][0] = EArtList::Test;
	TileGrid[Height - 1][Width - 1] = ETile::DemonLordCastle;
	TileArtGrid[Height - 1][Width - 1] = EArtList::Castle1;
}
