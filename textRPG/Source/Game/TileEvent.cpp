#include "TileEvent.h"

#include "Managers/GameManager.h"
#include "Managers/UIManager.h"
#include "InputReceiver.h"
#include "AudioPlayer.h"
#include "LogicHelper.h"
#include "ConstantContainer.h"
#include "Character.h"

TileEvent::TileEvent()
{
	Sentences = GenerateEventDialogue();
	PlaceHolders = GeneratePlaceHolders();
	UIManagerInstance = GameManager::GetInstance().GetUIManager();
}

TileEvent::~TileEvent()
{
}

void TileEvent::Run()
{
	// 다이얼로그 출력 전 혹은 후에 작업할 것이 있으면 처리

	PerformDialogue();
}

void TileEvent::PerformDialogue()
{
	int CurrentSentenceIndex = 0;
	// 대화 출력 후에 대기 여부. 선택지 입력 후에는 대기할 필요가 없으므로 그 떄 사용한다.
	bool bShouldWait = true;
	while (CurrentSentenceIndex < Sentences.size() && CurrentSentenceIndex >= 0)
	{
		bShouldWait = true;
		FSentence& Sentence = Sentences[CurrentSentenceIndex];

		DrawSentence(Sentence);
		CurrentSentenceIndex = Sentence.NextNodeID;

		// 선택지 처리
		if (Sentence.HasChoice())
		{
			// 입력 처리. 1, 2를 선택 받는다.
			EKey InputKey = EKey::Key_0;
			do {
				InputKey = InputReceiver::ChatchInput();
			} while (InputKey != EKey::Key_1 && InputKey != EKey::Key_2);

			// 선택지는 반드시 2개 있다고 가정한다. 만약에 확장할 경우 반드시 수정할 것
			int Choice = InputKey == EKey::Key_1 ? 0 : 1;
			CurrentSentenceIndex = Sentence.Choices[Choice].NextID;
			bShouldWait = false;
		}

		// 대사 이외의 처리
		if (Sentence.TriggerEvent && !GameManager::GetInstance().IsSpecialEventActivated())
		{
			GameManager::GetInstance().SetSpecialEventActive(true);
			Character& Player = Character::GetInstance();
			Status& PlayerStatus = Player.GetStatus();
			PlayerStatus.SetStat(EStat::CurHp, PostEventHealthAmount);
		}

		if (bShouldWait)
		{
			LogicHelper::SleepFor(AutoTextDelay);
		}
	}
}

void TileEvent::DrawSentence(const FSentence& Sentence)
{
	// 현재 None이 없기 때문에 임시로 Armor를 None 대신 사용
	if (Sentence.CenterArt != EArtList::Armor && Sentence.CenterArt != CurrentCenterArt)
	{
		const FASCIIArtContainer& CenterArt = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(Sentence.CenterArt);
		UIManagerInstance->ChangeBasicCanvasArtImage(CenterArt, false);
	}

	UIManagerInstance->ClearMessageToBasicCanvasEventInfoUI(false);
	// 화자가 없는 대사도 있을 수 있다. 해당 부분은 출력하지 않도록 한다.
	if (!Sentence.Author.empty())
	{
		std::wstring AuthorString = FormatTextWithPlaceholder(Sentence.Author, PlaceHolders);
		UIManagerInstance->AddMessageToBasicCanvasEventInfoUI(AuthorString, false);
	}
	UIManagerInstance->AddMessageToBasicCanvasEventInfoUI(Sentence.Sentene, false);

	// 선택지 2개가 모두 존재할 경우에만 출력
	if (Sentence.HasChoice())
	{
		std::wstring ChoiceSentence1 = FormatChoiceStr(1, Sentence.Choices[0].ChoiceSentence);
		std::wstring ChoiceSentence2 = FormatChoiceStr(2, Sentence.Choices[1].ChoiceSentence);
		UIManagerInstance->AddMessageToBasicCanvasEventInfoUI(ChoiceSentence1, false);
		UIManagerInstance->AddMessageToBasicCanvasEventInfoUI(ChoiceSentence2, false);
	}

	// 현재 잘못된 인자가 넘어갈 수 있는 부분은 확인하고 있지 않다.
	// 데이터 작성에 주의할 것
	if (!Sentence.SoundSFX.empty())
	{
		AudioPlayer::Play(Sentence.SoundSFX);
	}

	UIManagerInstance->PrintUI(ERenderingCanvas::Basic);
}

std::wstring TileEvent::FormatTextWithPlaceholder(const std::wstring& Text, const std::unordered_map<std::wstring, std::wstring>& PlaceHolders)
{
	std::wstring Result;
	size_t Start = 0;

	// 반복적인 치환 로직에 따라 PlaceHolder를 치환
	while (Start < Text.size())
	{
		size_t OpenBrace = Text.find(L"{", Start);
		// 더 이상 PlaceHolder가 없으면 나머지 택스트 전부 추가
		if (OpenBrace == std::wstring::npos)
		{
			Result += Text.substr(Start);
			break;
		}

		// { 이후의 }를 검색
		size_t CloseBrace = Text.find(L"}", OpenBrace);
		// 닫히지 않는 경우는 나머지를 출력한다.
		// 추후에 변경 가능성 있음
		if (CloseBrace == std::wstring::npos)
		{
			Result += Text.substr(Start);
			break;
		}

		// {}를 찾은 상태
		// {이전 단어를 추가
		Result += Text.substr(Start, OpenBrace - Start);

		// PlaceHolder Key를 추출
		// 01234
		// {ABC}: OpenBrace : 0, CloseBrace : 4, CloseBrace - OpenBrace - 1 : 3
		std::wstring PlaceHolderKey = Text.substr(OpenBrace + 1, CloseBrace - OpenBrace - 1);

		if (PlaceHolders.find(PlaceHolderKey) != PlaceHolders.end())
		{
			Result += PlaceHolders.at(PlaceHolderKey);
		}
		else
		{
			Result += L"{" + PlaceHolderKey + L"}";
		}

		// 다음 검색 위치를 갱신
		Start = CloseBrace + 1;
	}

	return Result;
}

std::vector<FSentence> TileEvent::GenerateEventDialogue()
{
	// NodeID : 0 order로 설정
	// 	int NodeID,	EArtList, std::wstring Author, std::wstring Sentene, std::string SoundSFX, FChoice[2], bool TriggerEvent
	// FSentence sentence = { 0, EArtList::Armor, L"Author", L"Sentence", "SoundSFX", /* FChoice */{{"Choice1", Next1}, {"Choice2", Next2}}, false };
	FSentence sentence = { 0, 1, EArtList::Orc, L"리산나", L"난 마녀가 아니야! 나는 왕실 연금술사였지만, 왕의 타락을 보고 도망쳤을 뿐이야.", "", { {L"", 0}, {L"", 0} }, false };
	std::vector<FSentence> Result = {
		{ 0, 1, EArtList::Orc, L"리산나", L"난 마녀가 아니야! 나는 왕실 연금술사였지만, 왕의 타락을 보고 도망쳤을 뿐이야.", "", { {L"", 0}, {L"", 0} }, false },
		{ 1, 2, EArtList::Orc, L"리산나", L"왕은 지금 끔찍한 일을 꾸미고 있어. 제발 내 말을 믿어줘!!", "", { {L"", 0}, {L"", 0} }, false },
		{ 2, 3, EArtList::Slime, L"성난 민중", L"됬고 포션을 내놔. 그러면 목숨은 살려주지", "", { {L"", 0}, {L"", 0}}, false },
		{ 3, 4,EArtList::Orc, L"리산나", L"그게 마지막이었어. 제발 나를 놓아줘.", "", { {L"", 0}, {L"", 0}}, false },
		{ 4, 5,EArtList::Slime, L"성난 민중", L"그건 확인해봐야 알 일이지", AudioPath::NORMALATTACK, { {L"", 0}, {L"", 0}}, false },
		{ 5, -1,EArtList::Devil, L"{Player}", L"\'이런 큰일이야. 나는 어떻게 해야하지?\'", "", { {L"그녀를 돕는다", 6}, {L"그녀를 돕지 않는다.", 10}}, false},
		// 그녀를 돕는다 선택지
		{ 6, 7,EArtList::Devil, L"{Player}", L"\'불의를 보고 넘어갈 수 없지\'", "", { {L"", 0}, {L"", 0}}, false },
		{ 7, 8,EArtList::Devil, L"{Player}", L"거기까지다.", AudioPath::NORMALATTACK, { {L"", 0}, {L"", 0}}, false },
		{ 8, 9,EArtList::Devil, L"", L"당신의 위협에 성난 민중들은 물러갔다.", "", { {L"", 0}, {L"", 0}}, true },
		{ 9, -1,EArtList::Orc, L"리산나", L"고맙습니다. 추가 작성", "", { {L"", 0}, {L"", 0}}, false }, // 종료
		// 그녀를 돕지 않는다 선택지
		{ 10, 11, EArtList::Devil, L"{Player}", L"\'아쉽지만 마녀를 돕는 것은 안 되.\'", "", { {L"", 0}, {L"", 0}}, false },
		{ 11, -1, EArtList::Devil, L"{Player}", L"\'그녀에게는 미안하지만 이것은 어쩔 수 없다.\' 추가 작성", "", { {L"", 0}, {L"", 0}}, false }, // 종료
	};

	return Result;
}

std::unordered_map<std::wstring, std::wstring> TileEvent::GeneratePlaceHolders()
{
	std::unordered_map<std::wstring, std::wstring> result;
	
	std::string PlayerNameString = Character::GetInstance().GetName();
	result[L"Player"] = LogicHelper::StringToWString(PlayerNameString);

	return result;
}

std::wstring TileEvent::FormatChoiceStr(int ChoiceNumber, std::wstring ChoiceMessage)
{
	return std::to_wstring(ChoiceNumber) + L") " + ChoiceMessage;
}

bool FSentence::HasChoice() const
{
	return !Choices[0].ChoiceSentence.empty() && !Choices[1].ChoiceSentence.empty();
}