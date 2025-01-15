#include "TileMapScene.h"
#include "Battle/AutoBattle.h"
#include "Managers/GameManager.h"
#include "AssetHandler.h"
#include "LogicHelper.h"
#include "ConstantContainer.h"
#include "Village.h"

TileMapScene::TileMapScene()
{
}

TileMapScene::~TileMapScene()
{
}

void TileMapScene::PlayScene()
{
	// Initialize
	auto& UIManagerInstance = GameManager::GetInstance().GetUIManager();
	UIManagerInstance->BindAllDelegate();
	auto& Player = Character::GetInstance();
	Player.Notify();
	GameManager::GetInstance().InitShop();

	// 초기 상태 초기화 후 첫 화면 그리기
	auto& TileMapInstance = GameManager::GetInstance().GetTileMap();
	TileMapInstance->Move(0, 0);

	DrawField();

	// While : Character is Alive
	while (true)
	{
		EKey KeyInput = InputReceiver::ChatchInput();

		// 이동처리
		if (IsMoveInput(KeyInput))
		{
			std::pair<int, int> CurrentPosition = TileMapInstance->GetCurrentPosition();
			std::pair<int, int> NextPosition = CalculateNextPosition(CurrentPosition, KeyInput);

			if (TileMapInstance->CanTraverse(NextPosition.first, NextPosition.second))
			{
				// Move Code

				TileMapInstance->Move(NextPosition.first, NextPosition.second);
				// Play Move Sound
				AudioPlayer::Play(AudioPath::FOOTSTEPSFX_GRASS);

				// 도착한 Tile 처리
				if (TileMapInstance->GetCurrentTileType() == ETile::Blank
					&& LogicHelper::GetRandomNumber(0.0, 1.0) < EncounterProbability)
				{
					unique_ptr<AutoBattle> Battle = make_unique<AutoBattle>();
					Battle->StartBattle();
				}
			}
			else
			{
				// 이동 불가능 방향
				// 다음 입력을 시도하고, 변경이 없으므로 새로 UI를 그리지 않는다.
				continue;
			}
		}
		else if (IsInventoryInput(KeyInput))
		{
			// Inventory 열기 설정
		}
		else if (IsInteractionInput(KeyInput))
		{
			// 상호 작용 가능한 타일일 경우 상호작용을 실행한다.
			ETile CurrentTile = TileMapInstance->GetCurrentTileType();
			if (CurrentTile == ETile::Village1)
			{
				EArtList CurrentVillageArt = TileMapInstance->GetCurrentTileArt();
				Village village(Player, UIManagerInstance, CurrentVillageArt);
				village.Run();
			}
			else if (CurrentTile == ETile::Village2)
			{
				EArtList CurrentVillageArt = TileMapInstance->GetCurrentTileArt();
				Village village(Player, UIManagerInstance, CurrentVillageArt);
				village.Run();
			}
			else if (CurrentTile == ETile::DemonLordCastle)
			{
				
			}
		}
		// 유효하지 않은 입력일 경우 다음 입력을 기다린다.
		else {
			continue;
		}

		// 현재 화면에 변화가 있을 경우에만 그려져야 한다.
		// i.e. move를 호출한다거나
		// 아니면 캐릭터의 스탯이 변화한다거나
		DrawField();
		LogicHelper::SleepFor(MoveDelay);
	} // While End Main Loop
}

void TileMapScene::DrawField()
{
	auto& UIManagerInstance = GameManager::GetInstance().GetUIManager();
	auto& TileMapInstance = GameManager::GetInstance().GetTileMap();

	// 현재 타일 입장 택스트 출력
	std::wstring TileDescription = TileMapInstance->GetCurrentTileDescription();
	std::vector<std::wstring> TileDescLines = SplitByNewLine(TileDescription);
	for (std::wstring Description : TileDescLines)
	{
		UIManagerInstance->AddMessageToBasicCanvasEventInfoUI(Description, false);
	}

	EArtList CurrentTileArt = TileMapInstance->GetCurrentTileArt();
	const FASCIIArtContainer& FieldArtContainer = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(CurrentTileArt);
	pair<int, int> TileArtOffset = TileMapInstance->GetCurrentTileArtOffset();
	UIManagerInstance->ChangeBasicCanvasArtImage(FieldArtContainer, false, TileArtOffset.first, TileArtOffset.second);

	UIManagerInstance->PrintUI(ERenderingCanvas::Basic);
}

bool TileMapScene::IsMoveInput(EKey KeyInput) const
{
	return KeyInput == EKey::LeftArrow || KeyInput == EKey::UpArrow || KeyInput == EKey::RightArrow || KeyInput == EKey::DownArrow;
}

bool TileMapScene::IsInventoryInput(EKey KeyInput) const
{
	return KeyInput == EKey::I || KeyInput == EKey::i;
}

bool TileMapScene::IsInteractionInput(EKey KeyInput) const
{
	return KeyInput == EKey::Z || KeyInput == EKey::z;
}

std::pair<int, int> TileMapScene::CalculateNextPosition(std::pair<int, int> CurrentPosition, EKey KeyInput)
{
	switch (KeyInput)
	{
		case EKey::LeftArrow:
			CurrentPosition.second--;
			break;
		case EKey::UpArrow:
			CurrentPosition.first--;
			break;
		case EKey::RightArrow:
			CurrentPosition.second++;
			break;
		case EKey::DownArrow:
			CurrentPosition.first++;
			break;
		default:
			break;
	}
	return CurrentPosition;
}

std::vector<std::wstring> TileMapScene::SplitByNewLine(const std::wstring& Str)
{
	std::vector<std::wstring> Result;
	size_t Start = 0, End;

	while ((End = Str.find(L'\n', Start)) != std::wstring::npos)
	{
		Result.push_back(Str.substr(Start, End - Start));
		Start = End + 1;
	}

	Result.push_back(Str.substr(Start));

	return Result;
}
