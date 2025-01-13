#pragma once
#include <iostream>
#include <cmath>
#include <windows.h>
#include "../Creatures/Monster.h"
#include "../Creatures/MonsterFactory.h"
#include "../Character.h"
#include "../Managers/GameManager.h"
#include "../LogicHelper.h"
#include "../InputReceiver.h"

using namespace std;

class ABattle
{ 
protected:

	Monster*	Enemy;						// 전투중인 몬스터
	Character*	Player;						// 전투중인 캐릭터
	UIManager&	UI;							// UI에 로그 출력을 위해 선언
	EKey		Action;						// 플레이어의 행동 인덱스 ( 1 = 공격하기, 2 = 포션먹기 )
	
	bool		bGameFinished;				// 전투가 끝나면 True

	float		MonsterCriProb;				// 몬스터 치명타 확률
	float		MonsterMissProb;			// 몬스터가 공격시 빗나감 확률
	float		MonsterNormalProb;			// 몬스터 일반공격 확률
	float		MonsterCoefficientValue;	// 몬스터 보정계수

	float		PlayerCriProb;				// 플레이어 치명타 확률
	float		PlayerMissProb;				// 플레이어가 공격시 빗나감 확률
	float		PlayerNormalProb;			// 플레이어 일반공격 확률
	int			PotionEventStartingHp;		// 포션 마시는 체력 기준

	// 몬스터의 공격
	void MonsterAttackAction()
	{
		// 전투 종료시 리턴
		if (bGameFinished)
			return;

		// 플레이어의 정보를 가져옴
		int PlayerHP = Player->GetStatus().GetStat(EStat::CurHp);
		string PlayerName = Player->GetName();

		// 플레이어에게 데미지
		int Damage = Enemy->GetPower();
		//Player-> TakeDamage(Damage);
		
		// 로그 선언
		string DamageLog = PlayerName + "의 체력이" + to_string(Damage) + "만큼 깎였습니다.";
		string CurHpLog = PlayerName + "의 현재체력 : " + to_string(PlayerHP);
		string DeadLog = PlayerName + "(이)가 죽었습니다";
		wstring DamageLogToW = LogicHelper::StringToWString(DamageLog);
		wstring CurHpLogToW = LogicHelper::StringToWString(CurHpLog);
		wstring DeadLogToW = LogicHelper::StringToWString(DeadLog);

		// 로그 출력
		UI.AddMessageToBasicCanvasEventInfoUI(DamageLogToW);
		UI.AddMessageToBasicCanvasEventInfoUI(CurHpLogToW);

		// 연출용도로 잠시 대기
		Sleep(1000);

		// 플레이어가 죽었는지 판단
		if (Player->IsDead())
		{
			UI.AddMessageToBasicCanvasEventInfoUI(DeadLogToW);
			GameLose();
		}
	}

	// 플레이어 포션 복용
	void PotionAction()
	{
		// 전투 종료시 리턴
		if (bGameFinished)
			return;

		// 플레이어의 현재체력을 가져옴
		int PlayerHP = Player->GetStatus().GetStat(EStat::CurHp);
		string PlayerName = Player->GetName();

		// 플레이어의 체력 회복
		PlayerHP += 5;

		// 로그 선언
		string PotionLog = PlayerName + "의 체력이 찼습니다.";
		string CurHpLog = PlayerName + "의 현재체력 : " + to_string(PlayerHP);
		wstring PotionLogToW = LogicHelper::StringToWString(PotionLog);
		wstring CurHpLogToW = LogicHelper::StringToWString(CurHpLog);

		// 로그 출력
		UI.AddMessageToBasicCanvasEventInfoUI(PotionLogToW);
		UI.AddMessageToBasicCanvasEventInfoUI(CurHpLogToW);

		// 연출용도로 잠시 대기
		Sleep(1000);
	}

	// 플레이어의 공격
	void PlayerAttackAction()
	{
		// 전투 종료시 리턴
		if (bGameFinished)
			return;

		// 몬스터의 정보를 가져옴
		int EnemyHp = Enemy->GetCurHp();
		string EnemyName = Enemy->GetName();

		// 몬스터에게 데미지
		int Damage = Player->GetDamage();
		Enemy->TakeDamage(Damage);

		// 로그 선언
		string DamageLog = EnemyName + "의 체력이 : " + to_string(Damage) + "만큼 깎였습니다";
		string CurHpLog = EnemyName + "의 현재 체력 : " + to_string(EnemyHp);
		string DeadLog = EnemyName + "(이)가 죽었습니다";
		wstring DamageLogToW = LogicHelper::StringToWString(DamageLog);
		wstring CurHpLogToW = LogicHelper::StringToWString(CurHpLog);
		wstring DeadLogToW = LogicHelper::StringToWString(DeadLog);

		// 로그 출력
		UI.AddMessageToBasicCanvasEventInfoUI(DamageLogToW);
		UI.AddMessageToBasicCanvasEventInfoUI(CurHpLogToW);

		// 연출용도로 잠시 대기
		Sleep(1000);

		// 몬스터가 죽었는지 판단
		if (Enemy->IsDead())
		{
			UI.AddMessageToBasicCanvasEventInfoUI(DeadLogToW);
			GameWin();
		}
	}

	// (플레이어 체력) <= (포션을 먹는 기준 체력) True
	bool IsPotionEvent()
	{
		return (PotionEventStartingHp >= Player->GetStatus().GetStat(EStat::CurHp));
	}

	// 소멸자
	~ABattle()
	{
		Sleep(1000);
		cout << "전투 소멸자" << endl;
	}

private:

	// 몬스터 난이도에 따른 보정계수 계산 함수
	void SetMonsterCoEfficientValue()
	{
		MonsterCoefficientValue = 1;
		// 플레이어 레벨에 따라 변경하는 로직 필요
	}

	// 플레이어, 몬스터 빗나감 확률 계산 함수
	void SetMissProb()
	{
		/*--------------------------------------------------------------
		* 플레이어의 빗나감 확률 = (5 - 5(1 - e(-x / 100)))
		* 몬스터의 빗나감 확률 = (Easy = 5%, Normal = 3.75%, Hard = 2.5%) 
		--------------------------------------------------------------*/
		PlayerMissProb = 5 - 5 * (1 - exp(-(1.0 / 100) * 30));
		MonsterMissProb = 5 * (2 - MonsterCoefficientValue);
	}

	// 플레이어, 몬스터 치명타 확률 계산 함수
	void SetCriProb()
	{
		/*--------------------------------------------------------------
		* 플레이어 치명타 확률 = ( 70(1 - e(-x/20)) )
		* 몬스터 치명타 확률 = (Easy = 30%, Normal = 37.5%, Hard = 45%)
		--------------------------------------------------------------*/
		PlayerCriProb = 30 + 70 * (1 - exp(-(1.0 / 30 * 30)));
		MonsterCriProb = 30 * MonsterCoefficientValue;
	}

	// 플레이어, 몬스터 일반공격 확률 계산 함수
	void SetNormalProb()
	{
		/*--------------------------------------------------------------
		* 플레이어 일반공격 확률 = ( 100 - (치명타 + 빗나감) )
		* 몬스터 일반공격 확률 = ( 100 - (치명타 + 빗나감) )
		--------------------------------------------------------------*/
		PlayerNormalProb = 100 - (PlayerCriProb + PlayerMissProb);
		MonsterNormalProb = 100 - (MonsterCriProb + MonsterMissProb);
	}

	// 전투 승리시 수행하는 로직
	void GameWin()
	{
		// 플레이어 경험치 증가
		// 로그 선언
		string InfoLog = "전투를 승리했습니다 !";
		wstring InfoLogToW = LogicHelper::StringToWString(InfoLog);

		// 연출용도로 잠시 대기
		Sleep(1000);

		// 로그 출력
		UI.AddMessageToBasicCanvasEventInfoUI(InfoLogToW);

		// 전투 종료
		bGameFinished = true;
	}

	// 전투 패배시 수행하는 로직
	void GameLose()
	{
		// 로그 선언
		string InfoLog = "전투를 패배했습니다 !";
		wstring InfoLogToW = LogicHelper::StringToWString(InfoLog);

		// 연출용도로 잠시 대기
		Sleep(1000);
		
		// 로그 출력
		UI.AddMessageToBasicCanvasEventInfoUI(InfoLogToW);

		// 전투 종료
		bGameFinished = true;
	}

	// 전투 진행 순수가상함수
	virtual void Battle() = 0;

public:

	// 생성자
	ABattle(Character* Player) : bGameFinished(false), PotionEventStartingHp(50)
	{
		// 1.보정계수, 빗나감, 치명타, 일반공격 수치 계산
		SetMonsterCoEfficientValue();
		SetMissProb();
		SetCriProb();
		SetNormalProb();

		// 2. 랜덤 몬스터 생성
		//Enemy = new MonsterFactory()->Create();

		// 3. UI 변수 초기화
		UI = GameManager::GetInstance().GetUIManager();
		
		// 4. 캐릭터 변수 초기화
		this->Player = Player;
	
	}

	// 전투 시작을 알리는 함수
	void StartBattle()
	{
		Battle();
	}
};
