#include <iostream>
#include <cmath>
#include <windows.h>
#include "ABattle.h"
#include "../Creatures/Monster.h"
#include "../Creatures/MonstserFactoryManager.h"
#include "../Character.h"
#include "../Managers/GameManager.h"
#include "../LogicHelper.h"
#include "../InputReceiver.h"
#include "../ConstantContainer.h"

ABattle::ABattle()
{
	// 전투 BGM 재생
	AudioPlayer::PlayLoop(AudioPath::BATTLE_BGM, 0.2f);

	// 1.보정계수, 빗나감, 치명타, 일반공격 수치 계산
	SetMonsterCoEfficientValue();
	SetMissProb();
	SetCriProb();
	SetNormalProb();

	// 2. 캐릭터 변수 초기화
	this->Player = &Character::GetInstance();

	// 3. 랜덤 몬스터 생성
	Enemy = (new MonstserFactoryManager())->CreateRandomMonster(Player->GetLevel());

	// 4. UI 변수 초기화
	UI = GameManager::GetInstance().GetUIManager();

	// 5. 변수 초기값 지정
	bGameFinished = false;
	PotionEventStartingHp = 50;
}
// 몬스터의 공격
void ABattle::MonsterAttackAction()
{
	// 전투 종료시 리턴
	if (bGameFinished)
		return;

	// 로그 초기화
	UI->ClearMessageToBasicCanvasEventInfoUI(false);

	// 플레이어의 정보를 가져옴
	int PlayerHP = Player->GetStatus().GetStat(EStat::CurHp);
	string PlayerName = Player->GetName();

	// 로그 선언
	string DamageLog;
	string CurHpLog;
	string DeadLog = PlayerName + "(이)가 죽었습니다";;
	wstring DamageLogToW;
	wstring CurHpLogToW;
	wstring DeadLogToW;

	// 플레이어 현재 체력 출력
	CurHpLog = PlayerName + "의 현재체력 : " + to_string(Player->GetStatus().GetStat(EStat::CurHp));
	CurHpLogToW = LogicHelper::StringToWString(CurHpLog);
	UI->AddMessageToBasicCanvasEventInfoUI(CurHpLogToW);
	Sleep(1000);

	// 공격 타입 계산
	EAttackType AttackType = CalculateAttackProb(MonsterCriProb, MonsterMissProb, MonsterNormalProb);

	// 플레이어에게 데미지
	int Damage = Enemy->GetPower();

	// 공격 타입에 따라 공격 수행
	switch (AttackType)
	{
		case EAttackType::Critical:
			UI->SetConsoleColor(EUIColor::LightRed);
			Damage = Player->TakeDamage(Damage * 2);
			DamageLog = "치명타 ! " + PlayerName + "의 체력이 " + to_string(Damage) + "만큼 깎였습니다.";
			AudioPlayer::Play(AudioPath::CRITICALATTACK);
			break;
		case EAttackType::Miss:
			DamageLog = "공격이 빗나갔습니다 !";
			AudioPlayer::Play(AudioPath::MISS);
			break;
		case EAttackType::Normal:
			UI->SetConsoleColor(EUIColor::LightRed);
			Damage = Player->TakeDamage(Damage);
			DamageLog = PlayerName + "의 체력이 " + to_string(Damage) + "만큼 깎였습니다.";
			AudioPlayer::Play(AudioPath::NORMALATTACK);
			break;
	}

	// 로그 초기화
	CurHpLog = PlayerName + "의 피격 후 체력 : " + to_string(Player->GetStatus().GetStat(EStat::CurHp));
	DamageLogToW = LogicHelper::StringToWString(DamageLog);
	CurHpLogToW = LogicHelper::StringToWString(CurHpLog);
	DeadLogToW = LogicHelper::StringToWString(DeadLog);

	// 로그 출력
	UI->AddMessageToBasicCanvasEventInfoUI(DamageLogToW);

	Sleep(200);
	UI->SetConsoleColor(EUIColor::White_Default);
	Sleep(800);

	UI->AddMessageToBasicCanvasEventInfoUI(CurHpLogToW);

	// 연출용도로 잠시 대기
	Sleep(1000);

	// 플레이어가 죽었는지 판단
	if (Player->IsDead())
	{
		UI->AddMessageToBasicCanvasEventInfoUI(DeadLogToW);
		GameLose();
	}
}

// 플레이어 포션 복용
void ABattle::PotionAction()
{
	// 전투 종료시 리턴
	if (bGameFinished)
		return;

	UI->ClearMessageToBasicCanvasEventInfoUI(false);

	// 플레이어의 현재체력을 가져옴
	int PlayerHP = Player->GetStatus().GetStat(EStat::CurHp);
	string PlayerName = Player->GetName();

	// 플레이어의 체력 회복
	Player->UsePotion();

	// 로그 선언
	string PotionLog = PlayerName + "이 회복 물약을 사용했습니다.";
	string CurHpLog = PlayerName + "의 현재체력 : " + to_string(Player->GetStatus().GetStat(EStat::CurHp));
	wstring PotionLogToW = LogicHelper::StringToWString(PotionLog);
	wstring CurHpLogToW = LogicHelper::StringToWString(CurHpLog);

	// 로그 출력
	Sleep(1000);
	AudioPlayer::Play(AudioPath::POTION);
	UI->AddMessageToBasicCanvasEventInfoUI(PotionLogToW);

	Sleep(1000);
	UI->AddMessageToBasicCanvasEventInfoUI(CurHpLogToW);

	// 연출용도로 잠시 대기
	Sleep(1000);
}

// 플레이어의 공격
void ABattle::PlayerAttackAction()
{
	// 전투 종료시 리턴
	if (bGameFinished)
		return;

	// 로그 클리어
	UI->ClearMessageToBasicCanvasEventInfoUI(false);

	// 몬스터의 정보를 가져옴
	int EnemyHp = Enemy->GetCurHp();
	string EnemyName = Enemy->GetName();

	// 로그 선언
	string DamageLog;
	string CurHpLog;
	string DeadLog = EnemyName + "(이)가 죽었습니다";;
	wstring DamageLogToW;
	wstring CurHpLogToW;
	wstring DeadLogToW;

	// 몬스터 현재 체력 출력
	CurHpLog = EnemyName + "의 현재체력 : " + to_string(Enemy->GetCurHp());
	CurHpLogToW = LogicHelper::StringToWString(CurHpLog);
	UI->AddMessageToBasicCanvasEventInfoUI(CurHpLogToW);
	Sleep(1000);

	// 몬스터에게 데미지
	int Damage = Player->GetStatus().GetStat(EStat::Power);

	// 공격 타입 계산
	EAttackType AttackType = CalculateAttackProb(PlayerCriProb, PlayerMissProb, PlayerNormalProb);

	// 공격 타입에 따라 공격 수행
	switch (AttackType)
	{
		case EAttackType::Critical:
			UI->SetConsoleColor(EUIColor::LightRed);
			Damage = Enemy->TakeDamage(Damage * 2);
			DamageLog = "치명타 ! " + EnemyName + "의 체력이 " + to_string(int(Damage)) + "만큼 깎였습니다.";
			AudioPlayer::Play(AudioPath::CRITICALATTACK, 0.6f);
			break;
		case EAttackType::Miss:
			DamageLog = "공격이 빗나갔습니다 !";
			AudioPlayer::Play(AudioPath::MISS);
			break;
		case EAttackType::Normal:
			UI->SetConsoleColor(EUIColor::LightRed);
			Damage = Enemy->TakeDamage(Damage);
			DamageLog = EnemyName + "의 체력이 " + to_string(Damage) + "만큼 깎였습니다.";
			AudioPlayer::Play(AudioPath::NORMALATTACK);
			break;
	}

	// 로그 초기화
	CurHpLog = EnemyName + "의 피격 후 체력 : " + to_string(Enemy->GetCurHp());
	DamageLogToW = LogicHelper::StringToWString(DamageLog);
	CurHpLogToW = LogicHelper::StringToWString(CurHpLog);
	DeadLogToW = LogicHelper::StringToWString(DeadLog);

	UI->AddMessageToBasicCanvasEventInfoUI(DamageLogToW);

	Sleep(200);
	UI->SetConsoleColor(EUIColor::White_Default);
	Sleep(800);
	UI->AddMessageToBasicCanvasEventInfoUI(CurHpLogToW);

	// 연출용도로 잠시 대기
	Sleep(1000);

	// 몬스터가 죽었는지 판단
	if (Enemy->IsDead())
	{
		UI->AddMessageToBasicCanvasEventInfoUI(DeadLogToW);
		GameWin();
	}
}

// (플레이어 체력) <= (포션을 먹는 기준 체력) True
bool ABattle::IsPotionEvent()
{
	return (PotionEventStartingHp >= Player->GetStatus().GetStat(EStat::CurHp));
}

// 몬스터 난이도에 따른 보정계수 계산 함수
void ABattle::SetMonsterCoEfficientValue()
{
	MonsterCoefficientValue = 1;
	// 플레이어 레벨에 따라 변경하는 로직 필요
}

// 플레이어, 몬스터 빗나감 확률 계산 함수
void ABattle::SetMissProb()
{
	/*--------------------------------------------------------------
	* 플레이어의 빗나감 확률 = (5 - 5(1 - e(-x / 100)))
	* 몬스터의 빗나감 확률 = (Easy = 10%, Normal = 7.5%, Hard = 5.0%)
	--------------------------------------------------------------*/
	PlayerMissProb = 10 - 10 * (1 - exp(-(1.0 / 100) * 30));
	MonsterMissProb = 10 * (2 - MonsterCoefficientValue);
}

// 플레이어, 몬스터 치명타 확률 계산 함수
void ABattle::SetCriProb()
{
	/*--------------------------------------------------------------
	* 플레이어 치명타 확률 = ( 30 + 70(1 - e(-x/20)) )
	* 몬스터 치명타 확률 = (Easy = 30%, Normal = 37.5%, Hard = 45%)
	--------------------------------------------------------------*/
	PlayerCriProb = 30 + 70 * (1 - exp(-(1.0 / 30 * 30)));
	MonsterCriProb = 30 * MonsterCoefficientValue;
}

// 플레이어, 몬스터 일반공격 확률 계산 함수
void ABattle::SetNormalProb()
{
	/*--------------------------------------------------------------
	* 플레이어 일반공격 확률 = ( 100 - (치명타 + 빗나감) )
	* 몬스터 일반공격 확률 = ( 100 - (치명타 + 빗나감) )
	--------------------------------------------------------------*/
	PlayerNormalProb = 100 - (PlayerCriProb + PlayerMissProb);
	MonsterNormalProb = 100 - (MonsterCriProb + MonsterMissProb);
}

// 전투 승리시 수행하는 로직
void ABattle::GameWin()
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
}

// 전투 패배시 수행하는 로직
void ABattle::GameLose()
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

// 공격 확률을 바탕으로 계산
ABattle::EAttackType ABattle::CalculateAttackProb(float Critical, float Miss, float Normal)
{
	 // 0-99 사이의 랜덤 값 생성
    float randomValue = static_cast<float>(rand() % 100);
    
    // Critical 구간 (0 ~ Critical)
    if (randomValue < Critical) {
        return EAttackType::Critical;
    }
    // Miss 구간 (Critical ~ Critical + Miss)
    else if (randomValue < Critical + Miss) {
        return EAttackType::Miss;
    }
    // Normal 구간 (나머지)
	else {
		return EAttackType::Normal;
	}
}


// 전투 시작을 알리는 함수
void ABattle::StartBattle()
{
	Battle();
}

