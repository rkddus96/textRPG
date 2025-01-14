#include "AssetHandler.h"
#include <Windows.h>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt> // C++11 표준의 codecvt 사용
#include "LogicHelper.h"
#include <algorithm>
#include <filesystem>

AssetHandler::AssetHandler()
{
    ReadAllArts();
}

void AssetHandler::ReadAllArts()
{
    std::wstring FolderPath = L"Source\\Game\\Assets\\Art\\";

    try 
    {
        for (const auto& Entry : std::filesystem::directory_iterator(FolderPath))
        {
            if (Entry.is_regular_file()) 
            { 
                // 일반 파일인지 확인
                // 파일 이름 가져오기
                std::wstring FileName = Entry.path().filename().wstring();
                std::wcout << L"File Name: " << FileName << std::endl;

                // 파일 내용 읽기
                std::wifstream File(Entry.path());
                if (!File.is_open()) 
                {
                    std::wcerr << L"Failed to open file: " << FileName << std::endl;
                    continue;
                }

                FASCIIArtContainer ArtContainer;
                ArtContainer.ArtName = FileName;

                std::wstring Line;
                while (std::getline(File, Line)) 
                {
                    ArtContainer.ArtLines.push_back(Line);
                }

                ArtContainers.push_back(ArtContainer);

                File.close();
                std::wcout << L"--------------------------------------" << std::endl;
            }
        }

        std::sort(ArtContainers.begin(), ArtContainers.end(), [](const FASCIIArtContainer& ArtContainer1, const FASCIIArtContainer& ArtContainer2)->bool
            {
                return ArtContainer1.ArtName < ArtContainer2.ArtName;
            });
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void AssetHandler::ReadArt(const std::wstring& Filename)
{
    // 메모장 파일 경로
     const std::wstring& FilePath = L"Source\\Game\\Assets\\Art\\" + Filename + L".txt";

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
    FASCIIArtContainer ArtContainer;

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
