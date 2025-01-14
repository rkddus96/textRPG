#include "TileMapScene.h"

#include "Managers/GameManager.h"
#include "AssetHandler.h"
#include "LogicHelper.h"

TileMapScene::TileMapScene()
	:CurrentFieldArt(EArtList::Test)
{
}

TileMapScene::~TileMapScene()
{
}

void TileMapScene::PlayScene()
{
	auto& UIManagerInstance = GameManager::GetInstance().GetUIManager();
	UIManagerInstance->BindAllDelegate();

	// 초기 상태 초기화 후 첫 화면 그리기
	auto& TileMapInstance = GameManager::GetInstance().GetTileMap();
	TileMapInstance->Move(0, 0);
	CurrentFieldArt = TileMapInstance->GetCurrentTileArt();

	DrawField();
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
				CurrentFieldArt = TileMapInstance->GetCurrentTileArt();
				// Play Move Sound

				// Battle? Reward?
			}
			else
			{
				// 이동 불가능 방향
				// 다음 입력을 시도하고, 변경이 없으므로 새로 UI를 그리지 않는다.
				continue;
			}
		}
		// 현재 화면에 변화가 있을 경우에만 그려져야 한다.
		// i.e. move를 호출한다거나
		// 아니면 캐릭터의 스탯이 변화한다거나
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
