#pragma once
#include <iostream>
#include <Windows.h>
#include "../AudioPlayer.h"
#include "../Creatures/Monster.h"
#include "../Creatures/MonstserFactoryManager.h"
#include "../Character.h"
#include "../Managers/GameManager.h"
#include "../LogicHelper.h"
#include "../InputReceiver.h"
#include "../ConstantContainer.h"

using namespace std;

class ABattle
{ 
protected:

	shared_ptr<UIManager>	UI;				// UI에 로그 출력을 위해 선언
	unique_ptr<Monster>	Enemy;				// 전투중인 몬스터
	Character*	Player;						// 전투중인 캐릭터
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
	void MonsterAttackAction();

	// 플레이어 포션 복용
	void PotionAction();

	// 플레이어의 공격
	void PlayerAttackAction();

	// (플레이어 체력) <= (포션을 먹는 기준 체력) True
	bool IsPotionEvent();

	// 전투 승리시 수행하는 로직
	virtual void GameWin() = 0;

	// 전투 패배시 수행하는 로직
	virtual void GameLose() = 0;

	// 소멸자
	~ABattle();

private:

	// 공격 타입
	enum EAttackType
	{
		Critical,
		Miss,
		Normal
	};

	// 몬스터 난이도에 따른 보정계수 계산 함수
	void SetMonsterCoEfficientValue();

	// 플레이어, 몬스터 빗나감 확률 계산 함수
	void SetMissProb();

	// 플레이어, 몬스터 치명타 확률 계산 함수
	void SetCriProb();

	// 플레이어, 몬스터 일반공격 확률 계산 함수
	void SetNormalProb();

	// 공격 확률을 바탕으로 계산
	EAttackType CalculateAttackProb(float Critical, float Miss, float Normal);

	// 전투 진행 순수가상함수
	virtual void Battle() = 0;

public:

	// 생성자
	ABattle();

	// 전투 시작을 알리는 함수
	void StartBattle();
};
