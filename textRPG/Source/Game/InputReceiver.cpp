#include "InputReceiver.h"
#include <conio.h>  // _kbhit(), _getch()

InputReceiver::InputReceiver()
{
}

EKey InputReceiver::ChatchInput()
{
	int Key = _getch();  // 키 입력 받기

	if (Key == 224) // 화살표입력
	{
		Key = _getch();

		if (Key == 72)
		{
			std::cout << "You pressed Up Key!" << std::endl;
			return EKey::UpArrow;
		}
		else if (Key == 80)
		{
			std::cout << "You pressed Down Key!" << std::endl;
			return EKey::DownArrow;
		}
		else if (Key == 75)
		{
			std::cout << "You pressed Left Key!" << std::endl;
			return EKey::LeftArrow;
		}
		else if (Key == 77)
		{
			std::cout << "You pressed Right Key!" << std::endl;
			return EKey::RightArrow;
		}
	}
	else if (Key == 0) // 특수 키 비활성화
	{
		Key = _getch();
		std::cout << "UnAvailable Key! " << Key << std::endl;
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
	std::cout << "UnAvailable Key! " << Key << std::endl;
	return EKey::UnAvailable;
}

InputReceiver::~InputReceiver()
{
}
