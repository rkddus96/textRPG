#include "AutoBattle.h"


AutoBattle::AutoBattle()
{
	// 연출 용도로 잠시 대기
	Sleep(1000);

	// 전투 BGM 재생
	AudioPlayer::Play(AudioPath::BATTLE_BGM, 0.2f);

	// 랜덤 몬스터 생성
	Enemy = (new MonstserFactoryManager())->CreateRandomMonster(Player->GetLevel());

	// 몬스터 UI 출력
	UI->SetBasicCanvasLayerHide(false, EBasicCanvasLayer::MonsterInfo);
	UI->SetBasicCanvasMonsterInfoUI(Enemy->GetName(), Enemy->GetCurHp());

	Sleep(3000);
}

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
		{
			if (!IsPotionAction())
			{
				PlayerAttackAction();
			}
		}
		else
			PlayerAttackAction();

		MonsterAttackAction();
	}
}

// 전투 승리시 수행하는 로직
void AutoBattle::GameWin()
{
	UI->ClearMessageToBasicCanvasEventInfoUI(false);
	AudioPlayer::StopAll();

	// 플레이어 경험치 증가
	int Exp = Enemy->GetExp();
	int Gold = Enemy->GetMoney();

	// 로그 선언
	string InfoLog = "전투를 승리했습니다 !";
	string ExpLog;
	string GoldLog = "골드를 " + to_string(Gold) + "만큼 획득했습니다 !";
	wstring InfoLogToW = LogicHelper::StringToWString(InfoLog);
	wstring ExpLogToW;
	wstring GoldLogToW = LogicHelper::StringToWString(GoldLog);


	if (Player->GetLevel() >= 10)
	{
		ExpLog = "최대 레벨입니다 !";
	}
	else
	{
		Player->RaiseExp(Exp);
		ExpLog = "경험치를 " + to_string(Exp) + "만큼 획득했습니다 !";
	}

	// 재화 획득
	Player->RaiseGold(Gold);

	// 로그 출력
	Sleep(1000);
	AudioPlayer::Play(AudioPath::WIN, 0.5f);
	UI->AddMessageToBasicCanvasEventInfoUI(InfoLogToW);

	// 플레이어 레벨업
	Sleep(1000);
	ExpLogToW = LogicHelper::StringToWString(ExpLog);
	UI->AddMessageToBasicCanvasEventInfoUI(ExpLogToW);
	if (Player->GetExp() >= Player->GetMaxExp())
		Player->LevelUp();

	// 플레이어 골드 획득
	Sleep(1000);
	UI->AddMessageToBasicCanvasEventInfoUI(GoldLogToW);

	Sleep(1000);
	AudioPlayer::Play(AudioPath::RESULT);
	// 전투 종료
	bGameFinished = true;
}

// 전투 패배시 수행하는 로직
void AutoBattle::GameLose()
{
	UI->ClearMessageToBasicCanvasEventInfoUI(false);
	AudioPlayer::StopAll();

	// 로그 선언
	string InfoLog = "전투를 패배했습니다 !";
	wstring InfoLogToW = LogicHelper::StringToWString(InfoLog);

	// 연출용도로 잠시 대기
	Sleep(1000);
	AudioPlayer::Play(AudioPath::LOSE);
	// 로그 출력
	UI->AddMessageToBasicCanvasEventInfoUI(InfoLogToW);


	Sleep(1000);

	// 전투 종료
	bGameFinished = true;
}