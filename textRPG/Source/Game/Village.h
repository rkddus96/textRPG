#pragma once

#include <memory>
#include <unordered_map>
#include <functional>
#include "AssetHandler.h"
#include "InputReceiver.h"

class UIManager;
class Character;

/// <summary>
/// 마을에서의 대사 출력, 상호 작용 등을 하는 클래스
/// 매 번 새로 생성해서 사용한다.
/// </summary>
class Village
{
public:
	Village(Character& Player, std::shared_ptr<UIManager> UI, EArtList VillageArt);
	virtual ~Village() = default;

	void SetEventTrigger(bool bCanTriggerEvent)
	{
		this->bCanTriggerEvent = bCanTriggerEvent;
	}

	void SetHasShop(bool bHasShop)
	{
		this->bHasShop = bHasShop;
	}

	void SetHasChurch(bool bHasChurch)
	{
		this->bHasChurch = bHasChurch;
	}

	void SetArtOffset(int XOffset, int YOffset)
	{
		ArtOffset = {XOffset, YOffset};
	}

	void Run();

	/// <summary>
	/// 기본 대사, 이미지를 출력하고 선택지를 출력한다.
	/// </summary>
	void DrawDefaultScene();

protected:
	std::shared_ptr<UIManager> UIManagerInstance;
	Character& Player;	


	// 각각의 장소를 방문한 뒤를 담당할 함수들
	// 각각의 함수는 자기 자신이 입력을 처리하고 화면을 그린다.
	// 그 뒤에 다시 루프로 돌아오면 Village가 기본 상태로 복구한다.

	void VisitStore();
	void VisitChurch();
	void VisitEvent();
	void Exit();

private:
	/// <summary>
	/// 교회 존재 유무
	/// </summary>
	bool bHasChurch = true;
	/// <summary>
	/// Shop 존재 유무
	/// </summary>
	bool bHasShop = false;
	/// <summary>
	/// Event Trigger 발생 가능 여부
	/// </summary>
	bool bCanTriggerEvent = false;

	// 교회 관련 코드
	int DefaultHealCharge = 50;

	/// <summary>
	/// Village 루프 종료 조건
	/// </summary>
	bool bEndVillage = false;

	/// <summary>
	/// 기본 아트 이미지, 처음 들어오거나 다른 메뉴 끝나면 출력
	/// </summary>
	EArtList DefualtArt;
	/// <summary>
	/// 기본 아트 이미지 오프셋, 처음 들어오거나 다른 메뉴 끝나면 출력
	/// </summary>
	std::pair<int, int> ArtOffset;
	/// <summary>
	/// 기본 메시지, 처음 들어오거나 다른 메뉴 끝나면 출력
	/// </summary>
	std::wstring DefaultMessage;

	void BuildOptions();
	std::wstring FormatSelectionMessage(const std::vector<std::wstring>& OptionTexts) const;
	
	std::wstring DefulatSelectoinMessage;
	std::unordered_map<EKey, std::function<void()>> KeyMappingMap;
};