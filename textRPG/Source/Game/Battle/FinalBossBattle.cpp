#include "FinalBossBattle.h"

FinalBossBattle::FinalBossBattle()
{
	// 연출 용도로 잠시 대기
	Sleep(1000);

	// 전투 BGM 재생
	AudioPlayer::Play(AudioPath::FINALBOSS_BGM, 0.2f);

	// 보스 몬스터 생성
	Enemy = (new MonstserFactoryManager())->CreateMonster(EMonsterType::Devil);

	// 몬스터 UI 출력
	UI->SetBasicCanvasLayerHide(false, EBasicCanvasLayer::MonsterInfo);
	UI->SetBasicCanvasMonsterInfoUI(Enemy->GetName(), Enemy->GetCurHp());

	Sleep(3000);
}

void FinalBossBattle::Battle()
{
	// 로그 선언
	string InfoLog = "일반 전투가 시작되었습니다";
	string ActionLog = "액션을 설정해주세요 : 1. 공격하기 2. 포션 먹기 :";
	string WrongInputLog = "멍때리지마세요 !";
	wstring InfoLogToW = LogicHelper::StringToWString(InfoLog);
	wstring ActionLogToW = LogicHelper::StringToWString(ActionLog);
	wstring WrongInputLogToW = LogicHelper::StringToWString(WrongInputLog);

	// 일반 전투가 시작되었습니다 !
	UI->AddMessageToBasicCanvasEventInfoUI(InfoLogToW);

	// 연출 용도로 잠시 대기
	Sleep(1000);

	// 전투가 종료될 때까지 반복
	while (!bGameFinished)
	{
		// 액션을 설정해주세요 : 1. 공격하기 2. 포션 먹기 :
		UI->AddMessageToBasicCanvasEventInfoUI(ActionLogToW);
		Action = InputReceiver::ChatchInput();

		switch (Action)
		{
		case EKey::Key_1:
			PlayerAttackAction();
			break;
		case EKey::Key_2:
			if (!IsPotionAction())
			{
				PlayerAttackAction();
			}
			break;
		default:
			// 잘못된 입력입니다.
			UI->AddMessageToBasicCanvasEventInfoUI(WrongInputLogToW);
			Sleep(1000);
			continue;
			break;
		}
		MonsterAttackAction();
	}
}

// 전투 승리시 수행하는 로직
void FinalBossBattle::GameWin()
{
	UI->ClearMessageToBasicCanvasEventInfoUI(false);
	AudioPlayer::StopAll();

	// 로그 선언
	string InfoLog = "전투를 승리했습니다 !";
	wstring InfoLogToW = LogicHelper::StringToWString(InfoLog);

	// 로그 출력
	Sleep(1000);
	AudioPlayer::Play(AudioPath::WIN, 0.5f);
	UI->AddMessageToBasicCanvasEventInfoUI(InfoLogToW);

	Sleep(1000);
	AudioPlayer::Play(AudioPath::RESULT);

	PrintRealEndingLog();
	// 전투 종료
	bGameFinished = true;
}

// 전투 패배시 수행하는 로직
void FinalBossBattle::GameLose()
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

void FinalBossBattle::PrintRealEndingLog()
{
	Sleep(1000);
	UI->ClearMessageToBasicCanvasEventInfoUI(false);

	// 로그 선언
	string endingLog1 = "리안나 : 네가 아니었으면 이 모든 걸 끝낼 수 없었을 거야.";
	string endingLog2 = "리안나 : 정말 고마워.";

	wstring endingLog1ToW = LogicHelper::StringToWString(endingLog1);
	wstring endingLog2ToW = LogicHelper::StringToWString(endingLog2);

	// 연출용도로 1초 간격으로 로그 출력
	Sleep(2000);
	UI->AddMessageToBasicCanvasEventInfoUI(endingLog1ToW);

	Sleep(2000);
	UI->AddMessageToBasicCanvasEventInfoUI(endingLog2ToW);

	Sleep(2000);
}