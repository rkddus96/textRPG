#pragma once
#include "ABattle.h"
#include "../Creatures/MonstserFactoryManager.h"
#include "FinalBossBattle.h"

class HandBattle : public ABattle
{
private:
	// 수동 전투 로직
	void Battle();

	// 게임 승리
	void GameWin();

	// 게임 패배
	void GameLose();

public:
	// 수동 전투 생성자
	HandBattle();
};