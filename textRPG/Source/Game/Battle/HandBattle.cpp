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
	wstring InfoLogToW = LogicHelper::StringToWString(InfoLog);


	// 로그 출력
	Sleep(1000);
	AudioPlayer::Play(AudioPath::WIN, 0.5f);
	UI->AddMessageToBasicCanvasEventInfoUI(InfoLogToW);


	Sleep(1000);
	AudioPlayer::Play(AudioPath::RESULT);
	// 전투 종료
	bGameFinished = true;

	PrintNormalEndingLog();
	// PrintFinalEndingLog();
	
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

void HandBattle::PrintFinalEndingLog()
{
	Sleep(1000);
	UI->ClearMessageToBasicCanvasEventInfoUI(false);

	// 로그 선언
	string endingLog1 = "리안나 : 축하하긴 아직 일러. 왕은 단지 꼭두각시에 불과해. 진짜 적은 따로있어.";
	string endingLog2 = "리안나 : 왕국은 오래전 마왕을 봉인한 뒤, 그의 힘을 이용해왔어.";
	string endingLog3 = "리안나 : 여자들을 제물로 바치며 병사들의 힘을 키우고, 성벽을 강화하며, 왕의 권력을 유지해온거야.";
	string endingLog4 = "리안나 : 하지만 봉인은 약해지고 있어. 마왕이 부활하면 이 세계는 끝장이야. 너만이 이걸 막을 수 있어.";
	string endingLog5 = "리안나 : 모든 걸 끝내려면 암흑의 심연으로 가야 해. 거기서 네가 필요로 하는 무기를 찾을 수 있을거야.";

	wstring endingLog1ToW = LogicHelper::StringToWString(endingLog1);
	wstring endingLog2ToW = LogicHelper::StringToWString(endingLog2);
	wstring endingLog3ToW = LogicHelper::StringToWString(endingLog3);
	wstring endingLog4ToW = LogicHelper::StringToWString(endingLog4);
	wstring endingLog5ToW = LogicHelper::StringToWString(endingLog5);

	// 연출용도로 1초 간격으로 로그 출력
	Sleep(2000);
	UI->AddMessageToBasicCanvasEventInfoUI(endingLog1ToW);

	Sleep(2000);
	UI->AddMessageToBasicCanvasEventInfoUI(endingLog2ToW);

	Sleep(2000);
	UI->AddMessageToBasicCanvasEventInfoUI(endingLog3ToW);

	Sleep(2000);
	UI->AddMessageToBasicCanvasEventInfoUI(endingLog4ToW);

	Sleep(2000);
	UI->AddMessageToBasicCanvasEventInfoUI(endingLog5ToW);

	Sleep(2000);
}