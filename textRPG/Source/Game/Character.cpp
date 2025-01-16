#define NOMINMAX // wihdow 헤더의 max min disable

#include <iostream>
#include <algorithm>
#include <random>
#include <memory>
#include <Windows.h>
#include "Character.h"
#include "IItem.h"
#include "InputReceiver.h"
#include "ConstantContainer.h"
#include "AudioPlayer.h"


Character::Character() : Level{ 1 }, MaxExp{ 100 }, Exp(0)
{
	JobList = {
			std::make_shared<Warrior>(),
			std::make_shared<Mage>(),
			std::make_shared<Thief>()
	};
	
	InitCharacter();
	RandomizeStats();

	Inventory.clear(); //Item 추가 시 추가
	
}

Character& Character::GetInstance() 
{
	static Character instance;
	
	return instance;
}

void Character::SetExp(int exp)
{
	Exp = std::max(0, exp);
	if (OnCharacterChanged)
	{
		OnCharacterChanged(ECharacterEvent::Exp, Exp);
	}
}

void Character::SetMaxExp(int max_exp)
{
	MaxExp = max_exp;
	if (OnCharacterChanged)
	{
		OnCharacterChanged(ECharacterEvent::MaxExp, max_exp);
	}
}

void Character::RaiseExp(int exp)
{
	if (Level >= 10)
	{
		Exp = std::min(MaxExp, Exp + exp);
	}
	else
	{
		Exp += exp;
		if (OnCharacterChanged)
		{
			OnCharacterChanged(ECharacterEvent::Exp, Exp);
		}
	}
	
}

void Character::SetLevel(int level)
{
	Level = std::max(1, std::min(level, 10));
	if (OnCharacterChanged)
	{
		OnCharacterChanged(ECharacterEvent::Level, Level);
	}
}

void Character::SetGold(int gold)
{
	Gold = gold;
	if (OnCharacterChanged)
	{
		OnCharacterChanged(ECharacterEvent::Gold, Gold);
	}
}

void Character::SetJob(std::shared_ptr<IJob> jobs)
{
	Jobs = jobs;
	if (OnCharacterChanged)
	{
		OnCharacterChanged(ECharacterEvent::Job, Jobs->GetJobNum());
	}
}

void Character::RaiseGold(int gold)
{
	Gold += gold;
	if (OnCharacterChanged)
	{
		OnCharacterChanged(ECharacterEvent::Gold, Gold);
	}
}


// 생존 여부 반환 함수
bool Character::IsDead()
{
	return (Stats.GetStat(EStat::CurHp) <= 0);

}

// 아이템 추가
void Character::AddItem(std::shared_ptr<IItem> item)
{
	Inventory.push_back(item);

	// 장비 아이템이면 바로 효과 적용
	if (item->IsConsumable() == false)
	{
		item->IsUsed(*this);
	}
	
	if (OnItemChanged)
	{
		OnItemChanged(Inventory);
	}
	
}

// 아이템 사용
void Character::UsePotion()
{	
	std::string CannotUsePotionLog;
	std::wstring CannotUsePotionLogW;
	CannotUsePotionLog = "인벤토리 내부에 포션이 없습니다.";

	CannotUsePotionLogW = LogicHelper::StringToWString(CannotUsePotionLog);
	

	for (int index = 0; index < Inventory.size(); index++)
	{
		if (Inventory[index]->IsConsumable())
		{
			Inventory[index]->IsUsed(*this);
			Inventory.erase(Inventory.begin() + index);
			if (OnItemChanged)
			{
				OnItemChanged(Inventory);
			}
			break;
		}
	}
	UI->AddMessageToBasicCanvasEventInfoUI(CannotUsePotionLogW);
	
}

int Character::TakeDamage(int rawdamage)
{
	Status& Stats = this->GetStatus();
	int Defense =Stats.GetStat(EStat::Defense);

	int damage = std::max((rawdamage - Defense), 0);
	int Hp = Stats.GetStat(EStat::CurHp) - damage;
	Stats.SetStat(EStat::CurHp, Hp);

	
	return damage;
}

// 캐릭터 생성 함수
void Character::InitCharacter()
{
	
	// string, wstring Log 선언
	std::string CharacterNameLog;
	std::string CharacterNameErrorLog;
	std::string ChooseJobLog;
	std::string WarriorExplainLog;
	std::string MageExplainLog;
	std::string ThiefExplainLog;
	std::string InputErrorLog;
	std::wstring CharacterNameLogW;
	std::wstring CharacterNameErrorLogW;
	std::wstring ChooseJobLogW;
	std::wstring WarriorExplainLogW;
	std::wstring MageExplainLogW;
	std::wstring ThiefExplainLogW;
	std::wstring InputErrorLogW;


	// string Log 초기화
	CharacterNameLog = "생성할 캐릭터의 이름을 입력해주세요: ";
	CharacterNameErrorLog = "이름을 입력하지 않았습니다. 다시 입력해주세요";
	ChooseJobLog = "직업을 선택해주세요.  ";
	WarriorExplainLog = "1. Warrior: Power를 주요 능력으로 하며, 맨 앞에서 전투를 수행하는 용맹한 전사입니다.   [ <-. 이전],[ z. 선택 ],[ ->. 다음  ]";
	MageExplainLog = "2. Mage: Defense를 주요 능력으로 하며, 적의 공격을 무력화시켜 몸을 지키는 마법의 대가입니다.   [ <-. 이전],[ z. 선택 ],[ ->. 다음  ]";
	ThiefExplainLog = "3. Thief: Luck을 주요 능력으로 하며, 운과 기술을 이용해 전장에서 살아남는 치명적인 전략가입니다.   [ <-. 이전],[ z. 선택 ],[ ->. 다음  ]";
	InputErrorLog = "잘못된 입력입니다. 다시 시도해주세요.";

	// wstring으로 변환
	CharacterNameLogW = LogicHelper::StringToWString(CharacterNameLog);
	CharacterNameErrorLogW = LogicHelper::StringToWString(CharacterNameErrorLog);
	ChooseJobLogW = LogicHelper::StringToWString(ChooseJobLog);
	WarriorExplainLogW = LogicHelper::StringToWString(WarriorExplainLog);
	MageExplainLogW = LogicHelper::StringToWString(MageExplainLog);
	ThiefExplainLogW = LogicHelper::StringToWString(ThiefExplainLog);
	InputErrorLogW = LogicHelper::StringToWString(InputErrorLog);

	
	//std::reference_wrapper 사용
	using ASCIIArtRef = std::reference_wrapper<const FASCIIArtContainer>;

	// 이미지 초기화
	const FASCIIArtContainer& WarriorContainer = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Warrior);
	const FASCIIArtContainer& MageContainer = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Mage);
	const FASCIIArtContainer& ThiefContainer = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Thief);

	// 이미지 리스트
	std::vector<ASCIIArtRef> JobContainerList = { WarriorContainer, MageContainer, ThiefContainer };


	//1. 이름 설정
	while (true)
	{

		// 로그 출력
//		UI->AddMessageToBasicCanvasEventInfoUI(CharacterNameLogW);
		std::cout << "생성할 캐릭터의 이름을 입력해주세요: ";
		
		std::getline(std::cin, Name);
		

		if (Name.empty())
		{
	//		UI->AddMessageToBasicCanvasEventInfoUI(CharacterNameErrorLogW);
			std::cout << "이름을 입력하지 않았습니다. 다시 입력해주세요" << std::endl;
		}
		else
		{
			break;
		}
	}

	AudioPlayer::Play(AudioPath::SELECT, 0.5f);

	
	std::vector<std::wstring> WLogList = { WarriorExplainLogW, MageExplainLogW, ThiefExplainLogW };
	std::vector<std::string> LogList = { WarriorExplainLog, MageExplainLog, ThiefExplainLog };
	int JobIndex = 0;
	bool bSelectJob = false;

	// 직업 설명 시작
	UI->AddMessageToBasicCanvasEventInfoUI(ChooseJobLogW);
	UI->ChangeBasicCanvasArtImage(JobContainerList[JobIndex]);
	UI->AddMessageToBasicCanvasEventInfoUI(WarriorExplainLogW);

	//2. 직업 선택
	while (true)
	{
		
	//	UI->AddMessageToBasicCanvasEventInfoUI(ThiefExplainLogW);

	//	std::cout << "직업을 선택해주세요." << std::endl;
	//	std::cout << "1. Warrior: Power를 주요 능력으로 하며, 맨 앞에서 전투를 수행하는 용맹한 전사입니다." << std::endl;
	//	std::cout << "2. Mage: Defense를 주요 능력으로 하며, 적의 공격을 무력화시켜 몸을 지키는 돕는 마법의 대가입니다." << std::endl;
	//	std::cout << "3. Thief: Luck을 주요 능력으로 하며, 운과 기술을 이용해 전장에서 살아남는 치명적인 전략가입니다. " << std::endl;
		
		EKey JobChoice = InputReceiver::ChatchInput();
	//	int JobChoice = 0;
	//	std::cin >> JobChoice;
		switch (JobChoice)
		{
		case EKey::LeftArrow:
			AudioPlayer::Play(AudioPath::SELECT, 0.5f);


			if (JobIndex > 0)
			{
				JobIndex--;
				// 초기화 후 다음 직업 설명
				UI->ClearMessageToBasicCanvasEventInfoUI(false);
				//이미지 출력
				UI->ChangeBasicCanvasArtImage(JobContainerList[JobIndex]);
				UI->AddMessageToBasicCanvasEventInfoUI(WLogList[JobIndex]);


				//	std::cout << LogList[JobIndex];
			}
			else
			{
				//	std::cout << "더 이상 뒤로 갈 수 없습니다.";
				UI->ClearMessageToBasicCanvasEventInfoUI(false);
				UI->AddMessageToBasicCanvasEventInfoUI(L"더 이상 이전으로 갈 수 없습니다.   [ <-. 이전],[ z. 선택 ],[ ->. 다음  ] ");
				Sleep(500);
			}
			break;

		case EKey::z:
			AudioPlayer::Play(AudioPath::SELECT, 0.5f);

			if (!JobList.empty() && JobIndex >= 0 && JobIndex < JobList.size())
			{
				Jobs = JobList[JobIndex];
				UI->AddMessageToBasicCanvasEventInfoUI(L"직업 선택을 완료했습니다.");
				//	std::cout << "직업 선택을 완료했습니다.";
				bSelectJob = true;
			} // 유효성 확인
			else
			{
				UI->ClearMessageToBasicCanvasEventInfoUI(false);
				UI->AddMessageToBasicCanvasEventInfoUI(L"유효하지 않은 선택입니다.");
				Sleep(500);
			}
			break;

		case EKey::RightArrow:
			AudioPlayer::Play(AudioPath::SELECT, 0.5f);


			if (JobIndex < JobList.size() - 1)
			{
				JobIndex++;
				//초기화 후 다음 직업 설명
				UI->ClearMessageToBasicCanvasEventInfoUI(false);
				UI->ChangeBasicCanvasArtImage(JobContainerList[JobIndex]);
				UI->AddMessageToBasicCanvasEventInfoUI(WLogList[JobIndex]);
				//	std::cout << LogList[JobIndex];
			}
			else
			{
				UI->ClearMessageToBasicCanvasEventInfoUI(false);
				UI->AddMessageToBasicCanvasEventInfoUI(L"더 이상 다음으로 갈 수 없습니다.   [ <-. 이전],[ z. 선택 ],[ ->. 다음  ]  ");
				Sleep(500);
				//	std::cout << "마지막 직업입니다.";
			}
			break;

		default:
			UI->ClearMessageToBasicCanvasEventInfoUI(false);
			UI->AddMessageToBasicCanvasEventInfoUI(L"잘못된 입력입니다. 다시 시도해주세요.   [ <-. 이전],[ z. 선택 ],[ ->. 다음  ]  ");
			Sleep(500);
			//	std::cout << "잘못된 입력입니다. 다시 시도해주세요." << std::endl;
		}

		if (bSelectJob)
		{
			break;
		}

	}

	UI->ClearMessageToBasicCanvasEventInfoUI(false);
}

// 스탯 설정 함수
void Character::RandomizeStats()
{
	// 시드 설정 및 난수 초기화
	std::random_device rd;
	std::mt19937 gen(rd());

	// 범위, 분포 설정
	std::uniform_int_distribution<> distHp(100, 130);
	std::uniform_int_distribution<> distPower(10, 15);
	std::uniform_int_distribution<> distDefense(3, 5);
	std::uniform_int_distribution<> distLuck(0, 10);

	std::cout << "이  름 : " << Name << std::endl;
	std::cout << "레  벨 : " << Level << std::endl;
	std::wcout << "직  업 : " << Jobs->GetJobName() << std::endl;

	bool bIsFirstSet = false;
	int maxHp;
	int power;
	int defense;
	int luck;

	int Choice = 0;
	while (true)
	{
		if (!bIsFirstSet)
		{
			// 최초 랜덤 스탯을 할당한다.
			maxHp = distHp(gen);
			power = distPower(gen);
			defense = distDefense(gen);
			luck = distLuck(gen);
			
			bIsFirstSet = true;
		}
		


		std::string StatLog;
		std::wstring StatLogW;
		StatLog = "체력 : " + std::to_string(maxHp) + " / " + std::to_string(maxHp) + ", 공격력 : " + std::to_string(power) + ", 방어력 : " + std::to_string(defense) + ", : 행운 : " + std::to_string(luck) + "   [z. 결정], [x. 재설정]";
		StatLogW = LogicHelper::StringToWString(StatLog);

		UI->ClearMessageToBasicCanvasEventInfoUI(false);
		UI->AddMessageToBasicCanvasEventInfoUI(StatLogW);
		

		//// 스탯 표시
		//std::cout << " 능력치를 설정해주세요!" << std::endl;
		//std::cout << "-------------------------------------------------" << std::endl;
		//std::cout << "                  PLAYER STATUS                  " << std::endl;
		//std::cout << "-------------------------------------------------" << std::endl;
		//std::cout << "체  력 : " << maxHp << "/" << maxHp << std::endl;
		//std::cout << "공격력 : " << power << std::endl;
		//std::cout << "방어력 : " << defense << std::endl;
		//std::cout << "행  운 : " << luck << std::endl;
		//std::cout << "-------------------------------------------------" << std::endl;
		//std::cout << "능력치를 확정하시겠습니까?" << std::endl;
		//std::cout << "1. 결정" << std::endl;
		//std::cout << "2. 재설정" << std::endl;
	//	std::cin >> Choice;
		EKey Choice = InputReceiver::ChatchInput();

		//// cin 에러 예외 처리
		//if (std::cin.fail())
		//{
		//	std::cin.clear();
		//	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		//	Choice = 0;
		//}

		EKey StatChoice = InputReceiver::ChatchInput();

		switch (StatChoice)
		{

		case EKey::z:
			AudioPlayer::Play(AudioPath::SELECT, 0.5f);

			// Stats에 저장, Damage 계산
			Stats.SetStat(EStat::MaxHp, maxHp);
			Stats.SetStat(EStat::CurHp, maxHp);
			Stats.SetStat(EStat::Power, power);
			Stats.SetStat(EStat::Defense, defense);
			Stats.SetStat(EStat::Luck, luck);

			UI->ClearMessageToBasicCanvasEventInfoUI(false);
			UI->AddMessageToBasicCanvasEventInfoUI(L"능력치가 확정되었습니다.");
			//	std::cout << "능력치가 확정되었습니다." << std::endl;
			break;

		case EKey::x:
			AudioPlayer::Play(AudioPath::SELECT, 0.5f);
			UI->ClearMessageToBasicCanvasEventInfoUI(false);
			UI->AddMessageToBasicCanvasEventInfoUI(L"스탯을 재설정합니다.");
			//	std::cout << "스탯을 재설정합니다." << std::endl;
				// 랜덤 스탯을 할당한다.
			maxHp = distHp(gen);
			power = distPower(gen);
			defense = distDefense(gen);
			luck = distLuck(gen);


			break;

		default:
			UI->ClearMessageToBasicCanvasEventInfoUI(false);
			UI->AddMessageToBasicCanvasEventInfoUI(L"잘못된 입력입니다. 다시 입력해주세요.");
			Sleep(500);
			//	std::cout << "잘못된 입력입니다. 다시 입력해주세요." << std::endl;
			break;
		}
		if (StatChoice == EKey::z)
		{
			break;
		}

	
	}
	// Damage 계산
	int powerWeight = Jobs->GetPowerWeight();
	int defenseWeight = Jobs->GetDefenseWeight();
	int luckWeight = Jobs->GetLuckWeight();

}

// 레벨업 함수
void Character::LevelUp()
{
	while (Exp >= MaxExp && Level < 10)
	{
		SetLevel(Level + 1);

		// 100이 넘어갔을 경우 초과치를 다음 경험치에 추가합니다.
		Exp = Exp - MaxExp;
		MaxExp += 50;

		
	}
	int maxHp = Stats.GetStat(EStat::MaxHp);
	int power = Stats.GetStat(EStat::Power);
	int defense = Stats.GetStat(EStat::Defense);
	int luck = Stats.GetStat(EStat::Luck);

	int pWeight = Jobs->GetPowerWeight();
	int dWeight = Jobs->GetDefenseWeight();
	int lWeight = Jobs->GetLuckWeight();

	maxHp += 20;
	power += pWeight;
	defense += dWeight;
	luck += lWeight;

	Stats.SetStat(EStat::MaxHp, maxHp);
	Stats.SetStat(EStat::Power, power);
	Stats.SetStat(EStat::Defense, defense);
	Stats.SetStat(EStat::Luck, luck);

	// 체력 회복
	Stats.SetStat(EStat::CurHp, maxHp);


	
}

void Character::Notify()
{
	SetExp(GetExp());
	SetLevel(GetLevel());
	SetGold(GetGold());
	
	Status& Stats = GetStatus();
	Stats.SetStat(EStat::CurHp, Stats.GetStat(EStat::CurHp));
	Stats.SetStat(EStat::Power, Stats.GetStat(EStat::Power));
	Stats.SetStat(EStat::Defense, Stats.GetStat(EStat::Defense));
	Stats.SetStat(EStat::Luck, Stats.GetStat(EStat::Luck));
	Stats.SetStat(EStat::MaxHp, Stats.GetStat(EStat::MaxHp));
	SetJob(GetJob());
	SetMaxExp(GetMaxExp());
}


// Character.cpp -> display 함수
void Character::DisplayInventory(int index)
{

	std::string ItemNameLog;
	std::string ItemPriceLog;
	std::string	ItemExplanationLog;

	std::wstring ItemNameLogW;
	std::wstring ItemPriceLogW;
	std::wstring ItemExplanationLogW;

	ItemNameLog = std::to_string(index + 1) + ". 이름: " + Inventory[index]->GetName() + "  가격: " + std::to_string(Inventory[index]->GetPrice()/2) + "  효과: " + Inventory[index]->GetExplanation() + "    [ <-   이전 페이지] [ ->   다음 페이지  ] [ z. 판매 ]  [ x. 뒤로 가기 ]";
	//	ItemPriceLog = 
	//	ItemExplanationLog = ;

	ItemNameLogW = LogicHelper::StringToWString(ItemNameLog);
	ItemPriceLogW = LogicHelper::StringToWString(ItemPriceLog);
	ItemExplanationLogW = LogicHelper::StringToWString(ItemExplanationLog);

	// 이미지 삽입
	UI->ChangeBasicCanvasArtImage(Inventory[index]->GetArtContainer());
	// 로그 출력
	UI->AddMessageToBasicCanvasEventInfoUI(ItemNameLogW);
	//	UI->AddMessageToBasicCanvasEventInfoUI(ItemPriceLogW);
	//	UI->AddMessageToBasicCanvasEventInfoUI(ItemExplanationLogW);



}