#pragma once
#include "ABattle.h"

class FinalBossBattle : public ABattle
{
private:
	// 최종보스 전투 로직
	void Battle();

public:
	// 최종보스 생성자
	FinalBossBattle();

};