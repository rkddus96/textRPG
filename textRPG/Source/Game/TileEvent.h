#pragma once

#include <string>
#include <vector>
#include <memory>
#include "AssetHandler.h"

struct FChoice
{
	std::wstring ChoiceSentence;
	int NextID;
};

struct FSentence
{
	int NodeID; // 노드 인덱스, 이동에 사용되므로 고유하고 순서대로 정렬되어야 한다.
	int NextNodeID; // 다음 노드 인덱스. 더 좋은 방법이 있겠지만 시간이 짧으므로 일일히 노드 인덱스를 설정. 범위 밖을 가리키면 대화는 종료된다. 대화를 종료시킬 때 이요할 것.
	EArtList CenterArt; // 중앙 이미지 설정, None이 존재하지 않으므로 기본값으로 설정되어 있으면 변경하지 않는다.
	std::wstring Author; // 화자 이름, 없을 경우 출력되지 않는다.
	std::wstring Sentene; // 대사, 화자 다음 줄에 출력된다.
	std::string SoundSFX; // ""일 경우 재생하지 않는다.
	FChoice Choices[2]; // FChoice : wstring ChoiceSentene, NextId : 다음으로 넘어갈 노드 ID
	bool TriggerEvent; // True일 경우 해당 이벤트를 활성화시킨다. 현재 이벤트는 하나이므로 따로 이벤트 이름을 기입하지 않는다.

	bool HasChoice() const;
};

/// <summary>
/// 현재 이벤트가 하나이므로 하나의 이벤트에 대한 데이터를 가지고 있도록 설정
/// </summary>
class TileEvent
{
public:
	TileEvent();
	~TileEvent();

	/// <summary>
	/// 현재 설정된 대사를 출력
	/// </summary>
	void Run();

protected:
	/// <summary>
	/// 대사가 넘어가는 시간
	/// </summary>
	int AutoTextDelay = 3000;

	int PostEventHealthAmount = 1;

	std::vector<FSentence> Sentences;
	EArtList CurrentCenterArt = EArtList::Armor;

	void PerformDialogue();
	void DrawSentence(const FSentence& Sentence);

	std::vector<FSentence> GenerateEventDialogue();

	std::shared_ptr<class UIManager> UIManagerInstance;

	static std::wstring FormatChoiceStr(int ChoiceNumber, std::wstring ChoiceMessage);
};
