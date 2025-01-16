#include "TileMapScene.h"
#include "Managers/GameManager.h"
#include "LogicHelper.h"
#include "ConstantContainer.h"
#include "AssetHandler.h"
#include "Village.h"
#include "TileEvent.h"
#include "Battle/AutoBattle.h"
#include "Battle/HandBattle.h"

TileMapScene::TileMapScene()
{
}

TileMapScene::~TileMapScene()
{
}

void TileMapScene::PlayScene()
{
	// 출력에 필요한 택스트 
	// 보스 배틀을 실행할 수 없을 때 출력되는 메시지, 추후 변경
	std::wstring BossBattleDeniedMessage = L"마왕성의 문은 강한 자만을 허락합니다. 당신의 레벨로는 아직 이 문을 열 수 없습니다.";
	std::wstring VillageEnterDeniedMessage = L"마녀를 도왔기 때문에 당신은 마을에 방문할 수 없습니다.";
	bool HasEventTriggered = false; // 임시 변수, 추후에 리펙토링으로 TileMap에서 해결할 수 있도록 해결한다.

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

	// While : Character is Alive 혹은 게임 클리어
	while (!Character::GetInstance().IsDead() && !GameManager::GetInstance().IsClearGame())
	{
		EKey KeyInput = InputReceiver::ChatchInput();
		bIsSceneInvalid = true;

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
			UIManagerInstance->OpenInventory();
		}
		else if (IsInteractionInput(KeyInput))
		{
			// Refactor: 추후에 타일 Class가 존재한다면 Tile Class의 정보를 바탕으로 생성

			// 상호 작용 가능한 타일일 경우 상호작용을 실행한다.
			ETile CurrentTile = TileMapInstance->GetCurrentTileType();
			// 특수 이벤트가 활성화되면 마을 진입이 불가능하다.
			// Village1 Type
			if (CurrentTile == ETile::Village1)
			{
				EArtList CurrentVillageArt = TileMapInstance->GetCurrentTileArt();
				Village village(Player, UIManagerInstance, CurrentVillageArt);
				village.SetHasShop(false);
				village.Run();
			}
			else if (CurrentTile == ETile::Village2)
			{
				// @Refactor
				// 전역 플래그가 없으니까 일단은 TileMapScene에서 관리
				// 진입 관련 처리는 Village가 나을 수 있으나 현재는 TileMapScene에서 관리
				// 처음 진입 시에 마을 이벤트를 발생
				if (!HasEventTriggered)
				{
					// Trigger Event
					HasEventTriggered = true;
					TileEvent TileEventInstance;
					TileEventInstance.Run();
				}

				bool CanEnterVillage = !GameManager::GetInstance().IsSpecialEventActivated();
				if (CanEnterVillage)
				{
					EArtList CurrentVillageArt = TileMapInstance->GetCurrentTileArt();
					Village village(Player, UIManagerInstance, CurrentVillageArt);
					village.SetHasShop(true);
					village.Run();
				}
				else
				{
					// Default Scene 출력을 방지하고 현재 출력으로 현재 프레임 종료
					UIManagerInstance->AddMessageToBasicCanvasEventInfoUI(VillageEnterDeniedMessage, true);
					bIsSceneInvalid = false;
				}
			}
			else if (CurrentTile == ETile::DemonLordCastle)
			{
				// Check Level
				if (Player.GetLevel() >= 10)
				{
					// Do Boss Battle
					std::unique_ptr<HandBattle> BossBattle = make_unique<HandBattle>();
					BossBattle->StartBattle();
				}
				else
				{
					// Default Scene 출력을 방지하고 현재 출력으로 현재 프레임 종료
					UIManagerInstance->AddMessageToBasicCanvasEventInfoUI(BossBattleDeniedMessage, true);
					bIsSceneInvalid = false;
				}
			}
		}
		// 유효하지 않은 입력일 경우 다음 입력을 기다린다.
		else {
			continue;
		}
		
		if (bIsSceneInvalid)
		{
			DrawField();
			LogicHelper::SleepFor(MoveDelay);
		}
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

	// 현재 타일 이미지 출력
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
