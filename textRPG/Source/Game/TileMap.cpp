#include "TileMap.h"

#include "LogicHelper.h"

TileMap::TileMap(int width, int height)
	:MapData(height, std::vector(width, ETile::Blank)), Width(width), Height(height)
{
	GenerateTestMap();
}

std::pair<int, int> TileMap::GetCurrentPosition() const
{
	return CurrentPlayerPosition;
}

void TileMap::Move(int nextX, int nextY)
{
	if (!CanTraverse(nextY, nextY))
	{
		// 필요할 경우 로깅 혹은 exeception 발생
		return;
	}
	CurrentPlayerPosition = {nextX, nextY};

	// 맵이 변경된 것을 알림
	OnMapChanged(GetCurretnMapData());
}

FAvailableDirection TileMap::GetAvailableDirection()
{
	FAvailableDirection direction;

	int x = CurrentPlayerPosition.first;
	int y = CurrentPlayerPosition.second;

	direction.bLeft = CanTraverse(x - 1, y);
	direction.bUp = CanTraverse(x, y - 1);
	direction.bRight = CanTraverse(x + 1, y);
	direction.bDown = CanTraverse(x, y + 1);

	return direction;
}

bool TileMap::CanTraverse(int x, int y) const
{
	return (x >= 0 && x < Width && y >= 0 && y < Height) && MapData[x][y] != ETile::Block;
}

std::vector<std::vector<ETile>> TileMap::GetCurretnMapData()
{
	std::vector<std::vector<ETile>> curMap = MapData;
	curMap[CurrentPlayerPosition.first][CurrentPlayerPosition.second] = ETile::Character;

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
