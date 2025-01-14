#include "TileMap.h"

#include "LogicHelper.h"

TileMap::TileMap(int Width, int Height)
	:TileGrid(Height, std::vector(Width, ETile::Blank)), TileArtGrid(Height, std::vector(Width, EArtList::Axe)), TileDescriptionGrid(Height, std::vector<std::wstring>(Width, L"")),
	Width(Width), Height(Height)
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

std::pair<int, int> TileMap::GetCurrentTileArtOffset() const
{
	auto iter = TileOffsetMap.find(GetCurrentTileArt());
	if (iter != TileOffsetMap.end())
	{
		return iter->second;
	}
	else
	{
		// 필요할 경우 로깅
		return {0, 0};
	}
}

std::wstring TileMap::GetCurrentTileDescription() const
{
	return TileDescriptionGrid[CurrentPlayerPosition.first][CurrentPlayerPosition.second];
}

ETile TileMap::GetCurrentTileType() const
{
	return TileGrid[CurrentPlayerPosition.first][CurrentPlayerPosition.second];
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
	// 태스트 맵에는 최소한 4 X 4 공간이 필요하다.
	if (Width <= 4 || Height <= 4) {
		// 필요하다면 Error 메시지
		// 게임을 실행할 수 없는 오류는 에러 메시지가 필요하다.
		return;
	}

	// 태스트맵에 사용할 타일 선언
	EArtList BlankTileList[] = {EArtList::Desert, EArtList::Landscape, EArtList::Mountain3, EArtList::Waterfall};
	std::wstring BlankDescriptionList[] = {L"태양 아래 황금빛 모래가 끝없이 펼쳐져 있으며, 뜨거운 바람이 피부를 자극한다."
											,L"푸른 초원이 끝없이 펼쳐지고, 바람에 풀잎이 흔들리며 평온한 분위기가 감돈다."
											, L"험난한 바위산과 눈 덮인 봉우리가 하늘을 찌를 듯 솟아있고, 차가운 바람이 몰아친다."
											, L"거대한 물줄기가 절벽에서 떨어져 내리며, 시원한 물보라가 공기 중에 흩날린다."};

	TileOffsetMap[EArtList::Desert] = {0, 0};
	TileOffsetMap[EArtList::Landscape] = { 0, 0 };
	TileOffsetMap[EArtList::Mountain3] = { 0, -30 };
	TileOffsetMap[EArtList::Waterfall] = { 5, -25 };

	for (int row = 0; row < Height; row++)
	{
		for (int col = 0; col < Width; col++)
		{
			int RandomBlankIndex = LogicHelper::GetRandomNumber(0, 3);
			TileArtGrid[row][col] = BlankTileList[RandomBlankIndex];
			TileDescriptionGrid[row][col] = BlankDescriptionList[RandomBlankIndex];
		}
	}

	// 좌상단이 마을, 우상단이 마을2, 우하단이 마왕성
	// To-Do : 초기화 과정에서 Tile Type과 Art Type을 한 번에 설정할 수 있도록 하는 기능 구현
	TileGrid[0][0] = ETile::Village1;
	TileArtGrid[0][0] = EArtList::Village1;
	TileDescriptionGrid[0][0] = L"에르발트는 솔반드리아 왕국에서 멀리 떨어진 평화로운 곳입니다.\n주변을 둘러보거나 마을 사람들과 대화하려면 Z키를 눌러 상호작용하세요.";

	TileGrid[Height - 1][0] = ETile::Village2;
	TileArtGrid[Height - 1][0] = EArtList::Village2;
	TileDescriptionGrid[Height - 1][0] = L"카르몬은 이제 무너진 건물과 자라난 잡초 속에 숨겨진 상처들만이 남아 있습니다.\n주변을 둘러보거나 마을 사람들과 대화하려면 Z키를 눌러 상호작용하세요.";

	// 마왕성 관련 설정
	// 마왕성 왼쪽
	TileArtGrid[Height - 2][Width - 1] = EArtList::CastleSmall;
	TileDescriptionGrid[Height - 2][Width - 1] = L"멀리서 솔반드리아 성의 거대한 탑이 보입니다. 그 위용은 마치 세상의 끝까지 닿을 듯한 느낌을 주며, 한 걸음 한 걸음이 더욱 무겁게 다가옵니다.";

	// 마왕성 위쪽
	TileArtGrid[Height - 1][Width - 2] = EArtList::CastleSmall;
	TileDescriptionGrid[Height - 1][Width - 2] = L"멀리서 솔반드리아 성의 거대한 탑이 보입니다. 그 위용은 마치 세상의 끝까지 닿을 듯한 느낌을 주며, 한 걸음 한 걸음이 더욱 무겁게 다가옵니다.";

	TileArtGrid[Height - 2][Width - 2] = EArtList::CastleSmall;
	TileDescriptionGrid[Height - 2][Width - 2] = L"멀리서 솔반드리아 성의 거대한 탑이 보입니다. 그 위용은 마치 세상의 끝까지 닿을 듯한 느낌을 주며, 한 걸음 한 걸음이 더욱 무겁게 다가옵니다.";

	TileGrid[Height - 1][Width - 1] = ETile::DemonLordCastle;
	TileArtGrid[Height - 1][Width - 1] = EArtList::Castle2;
	TileDescriptionGrid[Height - 1][Width - 1] = L"높이 솟은 탑과 차가운 돌벽이 솔반드리아 성을 감싸고 있습니다. 이곳에서 모든 진실이 드러날 것입니다.\nZ 키를 눌러 전투를 시작하세요.";
}
