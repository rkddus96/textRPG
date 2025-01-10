#include "AssetHandler.h"
#include <Windows.h>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt> // C++11 표준의 codecvt 사용
#include "LogicHelper.h"
#include <algorithm>

AssetHandler::AssetHandler()
{
    LogicHelper::GetConsoleSize(ConsoleWidth, ConsoleHeight);
    ReadArt(L"Test");
    ReadArt(L"Test2");
}

void AssetHandler::ReadArt(const std::wstring& Filename)
{
    // 메모장 파일 경로
     const std::wstring& FilePath = L"Assets\\Arts\\" + Filename + L".txt";

    // wifstream 객체 생성
    std::wifstream WIF(FilePath);

    // 파일 열기 확인
    if (!WIF.is_open()) 
    {
        LogicHelper::PrintWStringFast(L"파일을 열 수 없습니다: " + FilePath + L'\n');
        return;
    }

    // UTF-8 파일일 경우 로케일 설정
    //WIF.imbue(std::locale(WIF.getloc(), new std::codecvt_utf8<wchar_t>));

    // wstring으로 데이터 읽기
    std::wstring Content;
    std::wstring Line;

    int Width = 0;

    ASKIIArtContainer ArtContainer;

    while (std::getline(WIF, Line)) 
    {
        ArtContainer.ArtLines.push_back(Line);
        //Content += Line + L'\n';
        
        Width = max(Width, (int)Content.size());
    }

    ArtContainers.push_back(ArtContainer);

    //std::vector<std::wstring>& Lines = ArtContainer.ArtLines;

    // 모양 정사각형으로 만들기.
    // 필요 없나?
    /*for (auto& Line : Lines)
    {
        int LineSize = (int)Line.size();

        for (int i = LineSize; i < Width; ++i)
        {
            Line.push_back(L' ');
        }
        
    }*/


    WIF.close();
}

//void AssetHandler::GetConsoleSize(int& OutWidth, int& OutHeight)
//{
//    CONSOLE_SCREEN_BUFFER_INFO CSBI;
//
//    // 콘솔 핸들 가져오기
//    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//
//    if (GetConsoleScreenBufferInfo(ConsoleHandle, &CSBI))
//    {
//        // 콘솔 창의 크기 계산
//        OutWidth = CSBI.srWindow.Right - CSBI.srWindow.Left + 1;
//        OutHeight = CSBI.srWindow.Bottom - CSBI.srWindow.Top + 1;
//    }
//    else
//    {
//        // 오류 발생 시 기본값 설정
//        OutWidth = 0;
//        OutHeight = 0;
//        std::cerr << "Failed to get console size." << std::endl;
//    }
//}

AssetHandler::~AssetHandler()
{
}
