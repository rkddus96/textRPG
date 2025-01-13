#pragma once

#include <vector>
#include <functional>

enum class ETile
{
	Block, // 장애물
	Blank, // 공터
	DemonLordCastle, // 마왕성
	Villalge1, // 마을1
	Village2, // 마을2
	Vilalge2_Disable, // 사용불가 마을2
 	Character, // 캐릭터
	Count,
};

struct FAvailableDirection
{
	bool bLeft = false;
	bool bRight = false;
	bool bUp = false;
	bool bDown = false;
};

/// <summary>
/// 좌상단이 0, 0으로 시작해서 우하단이 (width - 1, height - 1)의 좌표를 가진다.
/// </summary>
class TileMap
{
public:
	TileMap(int Width, int Height);

	/// <summary>
	/// 현재 캐릭터의 위치를 반환한다.
	/// </summary>
	/// <returns>[x, y], x : [0, width - 1], y : [0, height - 1]</returns>
	std::pair<int, int> GetCurrentPosition() const;

	/// <summary>
	/// 현재 캐릭터의 위치를 이동한다. 이동할 수 없는 값이 주어질 경우 현재 위치를 유지한다.
	/// </summary>
	/// <param name="nextX">이동할 X 좌표</param>
	/// <param name="nextY">이동할 Y 좌표</param>
	void Move(int NextX, int NextY);

	/// <summary>
	/// 현재 위치에서 이동 가능한 방향을 반환한다.
	/// </summary>
	/// <returns>이동 가능 방향을 나타내는 FAvailableDirection을 반환</returns>
	FAvailableDirection GetAvailableDirection();

	std::function< void(std::vector<std::vector<ETile>>) > OnMapChanged;
	/// <summary>
	/// x, y 좌표로 이동 가능한지를 반환
	/// </summary>
	/// <param name="x">확인할 X 좌표</param>
	/// <param name="y">확인할 Y 좌표</param>
	/// <returns></returns>
	bool CanTraverse(int X, int Y) const;

	/// <summary>
	/// 현재 맵의 상태를 반환한다. 캐릭터가 마을, 마왕성과 겹쳐져 있을 경우 캐릭터가 우선시 된다.
	/// </summary>
	/// <returns>맵의 정보를 가진 2차원 배열</returns>
	std::vector<std::vector<ETile>> GetCurretnMapData();
	
protected:
	/// <summary>
	/// 무작위 맵을 생성한다.
	/// </summary>
	void GenerateRandomMap();

	/// <summary>
	/// 태스트 맵을 생성한다.
	/// </summary>
	void GenerateTestMap();
private:
	std::vector<std::vector<ETile>> MapData;
	int Width;
	int Height;
	std::pair<int, int> CurrentPlayerPosition;
};