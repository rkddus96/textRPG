#include "LogicHelper.h"
#include <Windows.h>
#include <iostream>
#include <random>

// 매크로 제거
#undef min
#undef max

std::string LogicHelper::WStringToString(const std::wstring& WStr)
{
    // UTF-8로 변환하기 위해 필요한 공간을 먼저 계산
    int Size = WideCharToMultiByte(CP_UTF8, 0, WStr.c_str(), -1, NULL, 0, NULL, NULL);

    // 변환된 문자열을 담을 버퍼를 생성
    std::string NewString(Size, 0);

    // 변환 수행
    WideCharToMultiByte(CP_UTF8, 0, WStr.c_str(), -1, &NewString[0], Size, NULL, NULL);

    return NewString;
}

std::string LogicHelper::WCharToString(wchar_t WChar)
{
    // 필요한 버퍼 크기 계산
    int Size = WideCharToMultiByte(CP_UTF8, 0, &WChar, 1, NULL, 0, NULL, NULL);

    // 변환된 문자열을 담을 버퍼를 생성
    std::string NewString(Size, 0);

    // 변환 수행
    WideCharToMultiByte(CP_UTF8, 0, &WChar, 1, &NewString[0], Size, NULL, NULL);

    return NewString;
}

std::wstring LogicHelper::StringToWString(const std::string& Str)
{
    // 필요한 wchar_t 배열 크기 계산
    int Size = MultiByteToWideChar(CP_UTF8, 0, Str.c_str(), -1, NULL, 0);

    // 변환된 문자열을 담을 버퍼 생성
    std::wstring NewWString(Size, 0);

    // 변환 수행
    MultiByteToWideChar(CP_UTF8, 0, Str.c_str(), -1, &NewWString[0], Size);

    return NewWString;
}

wchar_t LogicHelper::CharToWChar(char Char)
{
    // 필요한 wchar_t 배열 크기 계산
    wchar_t NewWChar;
    MultiByteToWideChar(CP_UTF8, 0, &Char, 1, &NewWChar, 1);
    return NewWChar;
}

void LogicHelper::PrintWStringFast(const std::wstring& WString)
{
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들 얻기
    //const char* RederingScreenUI = ScreenUI.c_str();

    DWORD Written;
    WriteConsoleW(ConsoleHandle, WString.c_str(), (DWORD)WString.size(), &Written, nullptr); // 빠르게 콘솔에 출력
}

void LogicHelper::GetConsoleSize(int& OutWidth, int& OutHeight)
{
    CONSOLE_SCREEN_BUFFER_INFO CSBI;

    // 콘솔 핸들 가져오기
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (GetConsoleScreenBufferInfo(ConsoleHandle, &CSBI))
    {
        // 콘솔 창의 크기 계산
        OutWidth = CSBI.srWindow.Right - CSBI.srWindow.Left + 1;
        OutHeight = CSBI.srWindow.Bottom - CSBI.srWindow.Top + 1;
    }
    else
    {
        // 오류 발생 시 기본값 설정
        OutWidth = 0;
        OutHeight = 0;
        std::cerr << "Failed to get console size." << std::endl;
    }
}

void LogicHelper::ClearConsole()
{
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO CSBI;
    DWORD DWSize, DWWritten;

    // 콘솔 버퍼 정보 얻기
    GetConsoleScreenBufferInfo(ConsoleHandle, &CSBI);

    // 콘솔 크기 계산
    DWSize = CSBI.dwSize.X * CSBI.dwSize.Y;

    // 화면 지우기
    FillConsoleOutputCharacter(ConsoleHandle, L' ', DWSize, { 0, 0 }, &DWWritten);
    FillConsoleOutputAttribute(ConsoleHandle, CSBI.wAttributes, DWSize, { 0, 0 }, &DWWritten);

    // 커서를 맨 위로 이동
    SetConsoleCursorPosition(ConsoleHandle, { 0, 0 });
}

void LogicHelper::SetFixedConsoleSize(int Width, int Height)
{

    HWND consoleWindow = GetConsoleWindow();  // 콘솔 창 핸들 가져오기
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // 콘솔 버퍼 크기 설정
    COORD bufferSize = { static_cast<SHORT>(Width), static_cast<SHORT>(Height) };
    SetConsoleScreenBufferSize(hOut, bufferSize);

    // 콘솔 창 크기 설정
    SMALL_RECT rect = { 0, 0, static_cast<SHORT>(Width - 1), static_cast<SHORT>(Height - 1) };
    SetConsoleWindowInfo(hOut, TRUE, &rect);

    // 크기 조정 방지
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    SetWindowLong(consoleWindow, GWL_STYLE, style & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX);
    
}

double LogicHelper::GetRandomNumber(double Min, double Max)
{
    std::random_device RandomDevice;
    std::mt19937 Genernator(RandomDevice());
    std::uniform_real_distribution Range(Min, Max);

    return Range(Genernator);
}

int LogicHelper::GetRandomNumber(int Min, int Max)
{
    std::random_device RandomDevice;
    std::mt19937 Genernator(RandomDevice());
    std::uniform_int_distribution Range(Min, Max);

    return Range(Genernator);
}

int LogicHelper::GetRandomNumberMaxRange()
{
    return LogicHelper::GetRandomNumber(std::numeric_limits<int>::min() , std::numeric_limits<int>::max());
}

