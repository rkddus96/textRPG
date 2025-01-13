#include "TileMap.h"

#include "LogicHelper.h"

TileMap::TileMap(int Width, int Height)
	:MapData(Height, std::vector(Width, ETile::Blank)), Width(Width), Height(Height)
{
	GenerateTestMap();
}

std::pair<int, int> TileMap::GetCurrentPosition() const
{
	return CurrentPlayerPosition;
}

void TileMap::Move(int NextX, int NextY)
{
	if (!CanTraverse(NextY, NextY))
	{
		// 필요할 경우 로깅 혹은 exeception 발생
		return;
	}
	CurrentPlayerPosition = {NextX, NextY};

	// 맵이 변경된 것을 알림
	OnMapChanged(GetCurretnMapData());
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
	return (X >= 0 && X < Width && Y >= 0 && Y < Height) && MapData[X][Y] != ETile::Block;
}

std::vector<std::vector<ETile>> TileMap::GetCurretnMapData()
{
	std::vector<std::vector<ETile>> CurrentMap = MapData;
	CurrentMap[CurrentPlayerPosition.first][CurrentPlayerPosition.second] = ETile::Character;

	return MapData;
}

void TileMap::GenerateRandomMap()
{
	int maxTileType = static_cast<int>(ETile::Count) - 1;

	for (int row = 0; row < Height; row++) {
		for(int col = 0; col < Width; col++) {
			MapData[row][col] = static_cast<ETile>(LogicHelper::GetRandomNumber(0, maxTileType));
		}
	}
}

void TileMap::GenerateTestMap()
{
	if (Width <= 0 || Height <= 0) {
		return;
	}

	// 좌상단이 마을, 우상단이 마을2, 우하단이 마왕성
	MapData[0][0] = ETile::Villalge1;
	MapData[Width - 1][0] = ETile::Village2;
	MapData[Width - 1][Height - 1] = ETile::DemonLordCastle;
}
