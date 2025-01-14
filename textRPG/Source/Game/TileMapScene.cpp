#include "TileMapScene.h"
#include "Battle/AutoBattle.h"
#include "Managers/GameManager.h"
#include "AssetHandler.h"
#include "LogicHelper.h"
#include "ConstantContainer.h"

TileMapScene::TileMapScene()
{
}

TileMapScene::~TileMapScene()
{
}

void TileMapScene::PlayScene()
{
	auto& UIManagerInstance = GameManager::GetInstance().GetUIManager();
	UIManagerInstance->BindAllDelegate();
	Character::GetInstance().Notify();

	// 초기 상태 초기화 후 첫 화면 그리기
	auto& TileMapInstance = GameManager::GetInstance().GetTileMap();
	TileMapInstance->Move(0, 0);

	DrawField();

	// While : Character is Alive
	while (true)
	{
		EKey KeyInput = InputReceiver::ChatchInput();

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
		// 유효하지 않은 입력일 경우 다음 입력을 기다린다.
		else {
			continue;
		}

		// 현재 화면에 변화가 있을 경우에만 그려져야 한다.
		// i.e. move를 호출한다거나
		// 아니면 캐릭터의 스탯이 변화한다거나
		DrawField();
	}

	// 게임 클리어 / 게임 오버 시에 따라 다른 텍스트를 출력
}

void TileMapScene::DrawField()
{
	auto& UIManagerInstance = GameManager::GetInstance().GetUIManager();
	auto& TileMapInstance = GameManager::GetInstance().GetTileMap();

	std::wstring TileDescription = TileMapInstance->GetCurrentTileDescription();
	UIManagerInstance->AddMessageToBasicCanvasEventInfoUI(TileDescription, false);

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
