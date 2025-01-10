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

    // wstring으로 데이터 읽기
    std::wstring Content;
    std::wstring Line;

    int Width = 0;

    FASKIIArtContainer ArtContainer;

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

AssetHandler::~AssetHandler()
{
}
