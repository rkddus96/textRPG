#include "AutoBattle.h"

void AutoBattle::Battle()
{
	// 로그 선언
	string InfoLog = "자동 전투가 시작되었습니다";
	wstring InfoLogToW = LogicHelper::StringToWString(InfoLog);

	// 자동 전투가 시작되었습니다 !
	UI->AddMessageToBasicCanvasEventInfoUI(InfoLogToW);

	// 연출 용도로 잠시 대기
	Sleep(1000);

	// 전투 종료가 될 때까지 반복
	while (!bGameFinished)
	{
		if (IsPotionEvent())
			PotionAction();
		else
			PlayerAttackAction();

		MonsterAttackAction();
	}
}