#include "HandBattle.h"


HandBattle::HandBattle()
{
	// 연출 용도로 잠시 대기
	Sleep(1000);

	// 전투 BGM 재생
	AudioPlayer::Play(AudioPath::BOSS_BGM, 0.2f);

	// 보스 몬스터 생성
	Enemy = (new MonstserFactoryManager())->CreateMonster(EMonsterType::King);

	// 몬스터 UI 출력
	UI->SetBasicCanvasLayerHide(false, EBasicCanvasLayer::MonsterInfo);
	UI->SetBasicCanvasMonsterInfoUI(Enemy->GetName(), Enemy->GetCurHp());

	Sleep(3000);
}

void HandBattle::Battle()
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
			PotionAction();
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
void HandBattle::GameWin()
{
	UI->ClearMessageToBasicCanvasEventInfoUI(false);
	AudioPlayer::StopAll();

	// 플레이어 경험치 증가
	int Exp = Enemy->GetExp();
	int Gold = Enemy->GetMoney();

	// 재화 획득
	Player->RaiseExp(Exp);
	Player->RaiseGold(Gold);


	// 로그 선언
	string InfoLog = "전투를 승리했습니다 !";
	string ExpLog = "경험치를 " + to_string(Exp) + "만큼 획득했습니다 !";
	string GoldLog = "골드를 " + to_string(Gold) + "만큼 획득했습니다 !";
	wstring InfoLogToW = LogicHelper::StringToWString(InfoLog);
	wstring ExpLogToW = LogicHelper::StringToWString(ExpLog);
	wstring GoldLogToW = LogicHelper::StringToWString(GoldLog);

	// 로그 출력
	Sleep(1000);
	AudioPlayer::Play(AudioPath::WIN, 0.5f);
	UI->AddMessageToBasicCanvasEventInfoUI(InfoLogToW);

	// 플레이어 레벨업
	Sleep(1000);
	UI->AddMessageToBasicCanvasEventInfoUI(ExpLogToW);
	if (Player->GetExp() + Exp >= Player->GetMaxExp())
		Player->LevelUp();

	// 플레이어 골드 획득
	Sleep(1000);
	UI->AddMessageToBasicCanvasEventInfoUI(GoldLogToW);

	Sleep(1000);
	AudioPlayer::Play(AudioPath::RESULT);
	// 전투 종료
	bGameFinished = true;

	PrintNormalEndingLog();

	// 최종 전투 시작
	unique_ptr<FinalBossBattle> finalBoss = make_unique<FinalBossBattle>();
	finalBoss->StartBattle();
}

// 전투 패배시 수행하는 로직
void HandBattle::GameLose()
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

void HandBattle::PrintNormalEndingLog()
{
	Sleep(1000);
	UI->ClearMessageToBasicCanvasEventInfoUI(false);

	// 로그 선언
	string endingLog1 = "정말 이게 끝일까 ?";
	string endingLog2 = "왕국이 다시 찾아오지 않을까 ?";
	string endingLog3 = "아니면 더 큰 위험이 도사리고 있는 건 아닐까 ?";

	wstring endingLog1ToW = LogicHelper::StringToWString(endingLog1);
	wstring endingLog2ToW = LogicHelper::StringToWString(endingLog2);
	wstring endingLog3ToW = LogicHelper::StringToWString(endingLog3);

	// 연출용도로 1초 간격으로 로그 출력
	Sleep(2000);
	UI->AddMessageToBasicCanvasEventInfoUI(endingLog1ToW);

	Sleep(2000);
	UI->AddMessageToBasicCanvasEventInfoUI(endingLog2ToW);

	Sleep(2000);
	UI->AddMessageToBasicCanvasEventInfoUI(endingLog3ToW);

	Sleep(2000);
}