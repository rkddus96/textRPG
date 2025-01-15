#pragma once
#include "ABattle.h"

class AutoBattle : public ABattle
{
private:

	// 자동 전투 로직
	void Battle();

	// 게임 승리
	void GameWin();

	// 게임 패배
	void GameLose();

public:

	// 자동 전투 생성자
	AutoBattle();
};