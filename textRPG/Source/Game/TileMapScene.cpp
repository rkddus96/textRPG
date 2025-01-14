#include "TileMapScene.h"
#include "Battle/AutoBattle.h"
#include "Managers/GameManager.h"
#include "AssetHandler.h"
#include "LogicHelper.h"

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

	GameManager::GetInstance().GetTileMap()->Move(0, 0);
	CurrentFieldArt = GameManager::GetInstance().GetTileMap()->GetCurrentTileArt();

	DrawField();
	while (true)
	{
		EKey KeyInput = InputReceiver::ChatchInput();

		if (IsMoveInput(KeyInput))
		{
			std::pair<int, int> CurrentPosition = GameManager::GetInstance().GetTileMap()->GetCurrentPosition();
			std::pair<int, int> NextPosition = CalculateNextPosition(CurrentPosition, KeyInput);

			if (GameManager::GetInstance().GetTileMap()->CanTraverse(NextPosition.first, NextPosition.second))
			{
				// Move Code

				GameManager::GetInstance().GetTileMap()->Move(NextPosition.first, NextPosition.second);
				CurrentFieldArt = GameManager::GetInstance().GetTileMap()->GetCurrentTileArt();
				// Play Move Sound

				// Battle? Reward?
				unique_ptr<AutoBattle> Battle = make_unique<AutoBattle>();
				Battle->StartBattle();
			}
			else
			{
				// 다음 입력 시도, 변경이 없으므로 새로 UI를 그리지 않는다.
				continue;
			}
		}

		DrawField();
	}
}

void TileMapScene::DrawField()
{
	auto& UIManagerInstance = GameManager::GetInstance().GetUIManager();

	std::wstring Message = L"이동 방향을 선택하세요(상, 하, 좌, 우)";

	UIManagerInstance->AddMessageToBasicCanvasEventInfoUI(Message);
	const FASKIIArtContainer& FieldArtContainer = GameManager::GetInstance().GetAssetHandler()->GetASKIIArtContainer(CurrentFieldArt);
	UIManagerInstance->ChangeBasicCanvasArtImage(FieldArtContainer);
	UIManagerInstance->PrintUI(ERenderingCanvas::Basic);
}

bool TileMapScene::IsMoveInput(EKey KeyInput) const
{
	return KeyInput == EKey::LeftArrow || KeyInput == EKey::UpArrow || KeyInput == EKey::RightArrow || KeyInput == EKey::DownArrow;
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
