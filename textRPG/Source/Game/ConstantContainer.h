#pragma once

#include<string>

namespace AudioPath
{
	extern const std::string TEST1;
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
}