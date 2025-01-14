#include "InputReceiver.h"
#include <conio.h>  // _kbhit(), _getch()
#include <Windows.h>

InputReceiver::InputReceiver()
{
}

EKey InputReceiver::ChatchInput()
{
	HANDLE InputHandle = GetStdHandle(STD_INPUT_HANDLE);
	FlushConsoleInputBuffer(InputHandle);

	int Key = _getch();  // 키 입력 받기

	if (Key == 224) // 화살표입력
	{
		Key = _getch();

		if (Key == 72)
		{
			return EKey::UpArrow;
		}
		else if (Key == 80)
		{
			return EKey::DownArrow;
		}
		else if (Key == 75)
		{
			return EKey::LeftArrow;
		}
		else if (Key == 77)
		{
			return EKey::RightArrow;
		}
	}
	else if (Key == 0) // 특수 키 비활성화
	{
		Key = _getch();
		return EKey::UnAvailable;
	}
	// Enter(키패드 포함), ESC, Tab, A~Z, a~z, 0~9(키패드 포함)
	else if (Key == (int)EKey::Enter || Key == (int)EKey::ESC || Key == (int)EKey::Tab ||
		(Key >= (int)EKey::A && Key <= (int)EKey::Z) ||
		(Key >= (int)EKey::a && Key <= (int)EKey::z) ||
		(Key >= (int)EKey::Key_0 && Key <= (int)EKey::Key_9))
	{
		return (EKey)Key;
	}

	// 그 외 사용 금지
	return EKey::UnAvailable;
}

InputReceiver::~InputReceiver()
{
}
