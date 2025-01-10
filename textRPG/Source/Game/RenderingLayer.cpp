#include "RenderingLayer.h"
#include <Windows.h>
#include "LogicHelper.h"

std::unordered_set<int> RenderingLayer::LayerIdSet;

RenderingLayer::RenderingLayer(int InLayerOrder, char InMask) :
	LayerOrder(InLayerOrder),
    Mask(LogicHelper::CharToWChar(InMask))
{
    InitLayer();
}

RenderingLayer::RenderingLayer(int InLayerOrder, wchar_t InMask) :
    LayerOrder(InLayerOrder),
    Mask(InMask)
{
    InitLayer();
}

void RenderingLayer::GetConsoleSize(int& OutWidth, int& OutHeight)
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

void RenderingLayer::RefreshLayer()
{
    int ConsoleWidth = 0;
    int ConsoleHeight = 0;

    GetConsoleSize(ConsoleWidth, ConsoleHeight);

    Layer.reserve(ConsoleWidth * ConsoleHeight);
    FreeViewLayer.reserve(ConsoleWidth * ConsoleHeight);
    UILines.resize(0);

    for (int i = 0; i < ConsoleHeight; ++i)
    {
        UILines.push_back(L"");

        for (int j = 0; j < ConsoleWidth; ++j)
        {
            if (j < ConsoleWidth - 1)
            {
                UILines[i].push_back(' ');
            }
            else
            {
                UILines[i].push_back('\n');
            }
        }
    }

    CombineUiLines();
}

void RenderingLayer::PrintCurrentLayer()
{
    if (UILines.size() <= 0)
    {
        std::cerr << "Cant Print Current Layer" << std::endl;
        return;
    }

    CombineUiLines();

    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들 얻기

    DWORD Written;
    WriteConsoleW(ConsoleHandle, FreeViewLayer.c_str(), (DWORD)FreeViewLayer.size(), &Written, nullptr); // 빠르게 콘솔에 출력
}

void RenderingLayer::DrawRectanlge(int PositionX, int PositionY, int Width, int Height)
{
    int ConsoleWidth = 0;
    int ConsoleHeight = 0;

    GetConsoleSize(ConsoleWidth, ConsoleHeight);

    int MaxX = PositionX + Height;
    int MaxY = PositionY + Width;

    if (ConsoleWidth <= MaxY || ConsoleHeight <= MaxX)
    {
        std::cout << "Cant Draw Rectangle" << std::endl;
        return;
    }

    for (int i = PositionX; i < MaxX; ++i)
    {
        for (int j = PositionY; j < MaxY; ++j)
        {
            if (i == PositionX)
            {
                if (j == PositionY)
                {
                    DrawWCharacter(i, j, L'┌');
                }
                else if (j == MaxY - 1)
                {
                    DrawWCharacter(i, j, L'┐');
                }
                else
                {
                    DrawWCharacter(i, j, L'─');
                }
            }
            else if (i == MaxX - 1)
            {
                if (j == PositionY)
                {
                    DrawWCharacter(i, j, L'└');
                }
                else if (j == MaxY - 1)
                {
                    DrawWCharacter(i, j, L'┘');
                }
                else
                {
                    DrawWCharacter(i, j, L'─');
                }
            }
            else
            {
                if (j == PositionY || j == MaxY - 1)
                {
                    DrawWCharacter(i, j, L'│');
                }
            }
        }
    }
}

void RenderingLayer::DrawWCharacter(int PositionX, int PositionY, wchar_t WChar)
{
    int ConsoleWidth = 0;
    int ConsoleHeight = 0;

    GetConsoleSize(ConsoleWidth, ConsoleHeight);

    if (ConsoleWidth - 1 < PositionY || ConsoleHeight - 1 < PositionX)
    {
        std::cout << "Cant Draw Character" << std::endl;
        return;
    }

    int LineSize = int(UILines[PositionX].size());
    wchar_t CurrentWChar = UILines[PositionX][PositionY];

    if (UILines[PositionX][PositionY] == WChar)
    {
        return;
    }

    // 한글이나 한자 뒤에 삽입 용도
    wchar_t VoidWChar = L'\u200B';

    if (LogicHelper::IsHangul(WChar) || LogicHelper::IsHanja(WChar))
    {
        // 줄의 마지막 문자는 \n이 들어있어서 건들면 안 됨..
        // 그리고 한글과 한자는 두 칸이기 때문에 맨 마지막 자리에는 삽입 불가
        if (PositionY >= LineSize - 2 || CurrentWChar == VoidWChar)
        {
            std::cout << "There is no Space for Hangle or Hanja " << std::endl;
            return;
        }
        
        UILines[PositionX][PositionY + 1] = VoidWChar;
    }
    else if (CurrentWChar == VoidWChar)
    {
        wchar_t& PrevWChar = UILines[PositionX][PositionY - 1];

        if (LogicHelper::IsHangul(PrevWChar) || LogicHelper::IsHanja(PrevWChar))
        {
            PrevWChar = L' ';
        }
    }

    UILines[PositionX][PositionY] = WChar;
}

void RenderingLayer::DrawString(int PositionX, int PositionY, const std::string& Str, wchar_t MaskWChar)
{
    std::wstring NewWString = LogicHelper::StringToWString(Str);
    DrawString(PositionX, PositionY, NewWString, MaskWChar);
}

void RenderingLayer::DrawString(int PositionX, int PositionY, const std::wstring& NewWString, wchar_t MaskWChar)
{
    int ConsoleWidth = 0;
    int ConsoleHeight = 0;

    GetConsoleSize(ConsoleWidth, ConsoleHeight);

    int Size = (int)NewWString.size();

    if (NewWString[Size - 1] == L'\0') // 마지막 널 문자이면 제거
    {
        Size--;
    }

    int MaxY = PositionY + Size;

    if (ConsoleWidth <= MaxY || ConsoleHeight <= PositionX)
    {
        std::cout << "Cant Draw String" << std::endl;
        return;
    }

    for (int i = 0, j = 0; i < Size; ++i)
    {
        wchar_t WChar = NewWString[i];

        if (WChar == MaskWChar)
        {
            continue;
        }

        DrawWCharacter(PositionX, PositionY + i + j, WChar);

        // 한글이나 한자이면 뒤에 공백 문자 삽입
        if (LogicHelper::IsHangul(WChar) || LogicHelper::IsHanja(WChar))
        {
            j++;
            DrawWCharacter(PositionX, PositionY + i + j, L'\u200B');
        }
    }
}

void RenderingLayer::DrawSurface(int StartPositionX, int StartPositionY, const std::vector<std::wstring>& Surface, wchar_t MaskWChar)
{
    for (auto& Line : Surface)
    {
        DrawString(StartPositionX++, StartPositionY, Line, MaskWChar);
    }
}

void RenderingLayer::CombineUiLines()
{
    Layer.resize(0);
    FreeViewLayer.reserve(0);

    for (int i = 0; i < UILines.size(); ++i)
    {
        Layer += UILines[i];
        for (int j = 0; j < UILines[i].size(); ++j)
        {
            if (UILines[i][j] == L'\u200B')
            {
                continue;
            }

            FreeViewLayer.push_back(UILines[i][j]);
        }
    }
}

void RenderingLayer::InitLayer()
{
    int tryingCount = 100;

    for (int i = 0; i < tryingCount; ++i)
    {
        LayerId = LogicHelper::GetRandomNumberMaxRange();

        if (LayerIdSet.find(LayerId) != LayerIdSet.end())
        {
            LayerIdSet.insert(LayerId);
            break;
        }

        if (i == tryingCount - 1)
        {
            LogicHelper::PrintWStringFast(L"Fail to generate id of LanderingLayer..");
            return;
        }
    }

    RefreshLayer();
}

RenderingLayer::~RenderingLayer()
{
}