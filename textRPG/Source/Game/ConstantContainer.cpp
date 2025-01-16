#include "ConstantContainer.h"

namespace AudioPath
{
	const std::string TEST1 = "Game Punch 2.wav";
	const std::string MISS = "Miss.wav";
	const std::string NORMALATTACK = "NormalAttack.wav";
	const std::string CRITICALATTACK = "CriticalAttack.wav";
	const std::string FOOTSTEPSFX_GRASS = "FootStepSFX_Grass.wav";
	const std::string WIN = "Win.wav";
	const std::string LOSE = "Lose.wav";
	const std::string RESULT = "Result.wav";
	const std::string POTION = "Potion.wav";
	const std::string BATTLE_BGM = "BattleBGM.wav";
	const std::string BOSS_BGM = "Boss.wav";
	const std::string FINALBOSS_BGM = "FinalBoss.wav";
	const std::string SELECT = "Select.wav";
	const std::string BOOK = "Book.wav";
	const std::string MAIN_BGM = "Main.wav";
	const std::string OPENING_PEACEFUL = "Epic Medieval - Memories.wav";  // 오프닝 씬 평화로운 브금
	const std::string OPENING_SERIOUS = "Epic Medieval - War.wav";   // 오프닝 씬 심각한 브금
}

namespace Battle
{
	const float CRITICAL = 1.2f;
}

namespace Console
{
	const int CONSOLE_WIDTH = 150;
	const int CONSOLE_HEIGHT = 51;
}

namespace UI
{
	const wchar_t EMPTY_CHAR = L'\u200B';
	const wchar_t USELESS_CHAR = L'綴';

	const int BACKGRUOND_BORDER_FIRST_POSITION_X = 1;
	const int BACKGROUND_BORDER_FIRST_POSITION_Y = 0;
	const int BACKGROUND_BORDER_WIDTH = 148;
	const int BACKGROUND_BORDER_HEIGHT = 49;

	const int EVENT_INFO_UI_CONTENTS_COUNT = 4;
	const int EVENT_INFO_UI_CONTENTS_FIRST_POSITION_X = 44;
	const int EVENT_INFO_UI_CONTENTS_FIRST_POSITION_Y = 4;
	const int EVENT_INFO_UI_CONTENT_ACTUAL_MAX_LENGTH = 140;

	const int EVENT_INFO_UI_BORDER_FIRST_POSITION_X = 43;
	const int EVENT_INFO_UI_BORDER_FIRST_POSITION_Y = 2;
	const int EVENT_INFO_UI_BORDER_WIDTH = 144;
	const int EVENT_INFO_UI_BORDER_HEIGHT = 6;

	const int STAT_INFO_UI_FIRST_POSITION_X = 3;
	const int STAT_INFO_UI_FIRST_POSITION_Y = 133;

	const int MIMIMAP_BORDER_UI_FIRST_POSITION_X = 2;
	const int MIMIMAP_BORDER_UI_FIRST_POSITION_Y = 2;

	const int PRESS_ENTER_KEY_TO_START_UI_POSITION_X = 42;
	const int PRESS_ENTER_KEY_TO_START_UI_POSITION_Y = 57;

	const int INVENTORY_BACKGROUND_FIRST_POSITION_X = 15;
	const int INVENTORY_BACKGROUND_FIRST_POSITION_Y = 15;

	const int CENTER_OF_UI_X = (EVENT_INFO_UI_BORDER_FIRST_POSITION_X - BACKGRUOND_BORDER_FIRST_POSITION_X) / 2;
	const int CENTER_OF_UI_Y = BACKGROUND_BORDER_FIRST_POSITION_Y + BACKGROUND_BORDER_WIDTH / 2;;
}