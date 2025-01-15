#pragma once

#include<string>

namespace AudioPath
{
	extern const std::string TEST1;
	extern const std::string CRITICALATTACK;
	extern const std::string NORMALATTACK;
	extern const std::string MISS;
	extern const std::string FOOTSTEPSFX_GRASS;
	extern const std::string CRITICALATTACK;	// 치명타 공격시
	extern const std::string NORMALATTACK;		// 일반 공격시
	extern const std::string MISS;				// 회피시
	extern const std::string WIN;				// 전투 승리시
	extern const std::string LOSE;				// 전투 패배시
	extern const std::string RESULT;			// 전투 보상 수령시
	extern const std::string POTION;			// 포션 사용시
	extern const std::string BATTLE_BGM;		// 전투 상태일 때의 브금
	extern const std::string BOSS_BGM;			// 보스 전투시
	extern const std::string FINALBOSS_BGM;		// 최종보스 전투시
	extern const std::string SELECT;			// 키보드 입력시
	extern const std::string BOOK;				// 책장 넘길 때
	extern const std::string MAIN_BGM;			// 메인화면 브금

}

namespace Console
{
	extern const int CONSOLE_WIDTH;
	extern const int CONSOLE_HEIGHT;
}

namespace UI
{
	// 두 칸 문자의 공간을 표시하거나 공백을 위한 문자
	extern const wchar_t EMPTY_CHAR;
	// 마스크로 쓰기 위한 의미 없는 문자
	extern const wchar_t USELESS_CHAR;

	extern const int BACKGRUOND_BORDER_FIRST_POSITION_X;
	extern const int BACKGROUND_BORDER_FIRST_POSITION_Y;
	extern const int BACKGROUND_BORDER_WIDTH;
	extern const int BACKGROUND_BORDER_HEIGHT;

	extern const int EVENT_INFO_UI_CONTENTS_COUNT;
	extern const int EVENT_INFO_UI_CONTENTS_FIRST_POSITION_X;
	extern const int EVENT_INFO_UI_CONTENTS_FIRST_POSITION_Y;
	extern const int EVENT_INFO_UI_CONTENT_ACTUAL_MAX_LENGTH;

	extern const int EVENT_INFO_UI_BORDER_FIRST_POSITION_X;
	extern const int EVENT_INFO_UI_BORDER_FIRST_POSITION_Y;
	extern const int EVENT_INFO_UI_BORDER_WIDTH;
	extern const int EVENT_INFO_UI_BORDER_HEIGHT;

	extern const int STAT_INFO_UI_FIRST_POSITION_X;
	extern const int STAT_INFO_UI_FIRST_POSITION_Y;

	extern const int MIMIMAP_BORDER_UI_FIRST_POSITION_X;
	extern const int MIMIMAP_BORDER_UI_FIRST_POSITION_Y;

	extern const int PRESS_ENTER_KEY_TO_START_UI_POSITION_X;
	extern const int PRESS_ENTER_KEY_TO_START_UI_POSITION_Y;

	extern const int INVENTORY_BACKGROUND_FIRST_POSITION_X;
	extern const int INVENTORY_BACKGROUND_FIRST_POSITION_Y;

	extern const int CENTER_OF_UI_X;
	extern const int CENTER_OF_UI_Y;
}