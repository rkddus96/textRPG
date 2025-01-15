#pragma once
#include "ABattle.h"

class FinalBossBattle : public ABattle
{
private:
	// 최종보스 전투 로직
	void Battle();

	// 게임 승리
	void GameWin();

	// 게임 패배
	void GameLose();
public:
	// 최종보스 생성자
	FinalBossBattle();

};