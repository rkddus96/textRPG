#pragma once

//void PrintColoredTextPerCharacter(const std::wstring& text, const std::vector<WORD>& colors)
//{
//    // 콘솔 핸들 얻기
//    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//
//    // 기존 콘솔 색상 저장
//    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
//    GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
//    WORD originalColor = consoleInfo.wAttributes;
//
//
//    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
//    // 글자마다 출력
//    size_t colorCount = colors.size();
//    for (size_t i = 0; i < text.size(); ++i)
//    {
//        // 색상 설정
//        WORD color = colors[i % colorCount]; // 색상 배열 순환
//        //SetConsoleTextAttribute(consoleHandle, color);
//
//        // 글자 출력
//        WriteConsoleW(consoleHandle, &text[i], 1, nullptr, nullptr);
//    }
//
//    // 색상 복원
//    SetConsoleTextAttribute(consoleHandle, originalColor);
//    std::wcout << std::endl;
//}
//
//void PrintColorSamples()
//{
//    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//
//    for (int color = 0; color < 16; ++color)
//    {
//        SetConsoleTextAttribute(consoleHandle, color);
//        std::cout << "Color " << color << " ";
//    }
//
//    // 기본 색상 복원
//    SetConsoleTextAttribute(consoleHandle, 7);
//    std::cout << std::endl;
//}

//extern void TestMain();

class MyTestScene
{
public:
	MyTestScene();

	void TestMain();
};