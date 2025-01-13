#pragma once
#include "ABattle.h"

class HandBattle : public ABattle
{
private:
	void Battle()
	{
		// 로그 선언
		string InfoLog = "일반 전투가 시작되었습니다";
		string ActionLog = "액션을 설정해주세요 : 1. 공격하기 2. 포션 먹기 :";
		string WrongInputLog = "잘못된 입력입니다.";
		wstring InfoLogToW = LogicHelper::StringToWString(InfoLog);
		wstring ActionLogToW = LogicHelper::StringToWString(ActionLog);
		wstring WrongInputLogToW = LogicHelper::StringToWString(WrongInputLog);

		// 일반 전투가 시작되었습니다 !
		UI.AddMessageToBasicCanvasEventInfoUI(InfoLogToW);

		// 연출 용도로 잠시 대기
		Sleep(1000);

		// 전투가 종료될 때까지 반복
		while (!bGameFinished)
		{
			// 액션을 설정해주세요 : 1. 공격하기 2. 포션 먹기 :
			UI.AddMessageToBasicCanvasEventInfoUI(ActionLogToW);
			Action = InputReceiver::ChatchInput();

			switch (Action)
			{
			case EKey::Key_1:
				PlayerAttackAction();
				break;
			case EKey::Key_2:
				PotionAction();
				break;
			default:
				// 잘못된 입력입니다.
				UI.AddMessageToBasicCanvasEventInfoUI(WrongInputLogToW);
				continue;
				break;
			}
			MonsterAttackAction();
		}
	}
};