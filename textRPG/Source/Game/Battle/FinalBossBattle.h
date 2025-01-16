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

	// 엔딩 로그 출력
	void PrintRealEndingLog();

public:
	// 최종보스 생성자
	FinalBossBattle();

};