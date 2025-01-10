#include "RenderingHandler.h"
#include "RenderingLayer.h"
#include <algorithm>
#include <Windows.h>
#include "ConstantContainer.h"

RenderingHandler::RenderingHandler() :
    ScreenUI(L"")
{
}

void RenderingHandler::PrintCurrentScreenUI()
{
    if (LayerList.size() <= 0)
    {
        // 로그
        return;
    }

    CombineLayers();
    //ClearConsole();

    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들 얻기

    DWORD Written;
    WriteConsoleW(ConsoleHandle, ScreenUI.c_str() , (DWORD)ScreenUI.size(), &Written, nullptr); // 빠르게 콘솔에 출력

}

void RenderingHandler::AddLayer(std::shared_ptr<RenderingLayer> NewLayerMask)
{
    LayerList.push_back(NewLayerMask);
}

void RenderingHandler::RemoveLayer(int LayerId)
{
    auto It = std::remove_if(LayerList.begin(), LayerList.end(), [&](std::shared_ptr<RenderingLayer> OtherLayer)-> bool
        {
            return LayerId == OtherLayer->GetLayerId();
        });

    if (It == LayerList.end())
    {
        return;
    }

    LayerList.erase(It);
}

void RenderingHandler::Clear()
{
    LayerList.resize(0);
}

void RenderingHandler::SortLayerInOrder()
{
	std::stable_sort(LayerList.begin(), LayerList.end(), 
		[](std::shared_ptr<RenderingLayer> Layer1, std::shared_ptr<RenderingLayer> Layer2)->bool
		{
			return Layer1->GetLayerOrder() < Layer2->GetLayerOrder();
		});
}

void RenderingHandler::CombineLayers()
{
    int LayerCount = (int)LayerList.size();
    if (LayerCount <= 0)
    {
        return;
    }

    ScreenUI.resize(0);
    SortLayerInOrder();

    std::wstring CombinedLayer = LayerList[0]->GetLayer();

    int CombinedLayerSize = (int)CombinedLayer.size();

    wchar_t EmptyChar = Char::EMPTY_CHAR;

    //for (int i = 1; i < LayerCount; ++i)
    //{
    //    const std::wstring& Layer = LayerList[i]->GetLayer();
    //    wchar_t Mask = LayerList[i]->GetMask();

    //    for (int j = 0; j < CombinedLayerSize; ++j)
    //    {
    //        wchar_t& OldCell = CombinedLayer[j];
    //        const wchar_t NewCell = Layer[j];
    //        wchar_t& PrevCell = CombinedLayer[j - 1];
    //        wchar_t& NextCell = CombinedLayer[j + 1];
    //        wchar_t& NextNextCell = CombinedLayer[j + 2];
    //        wchar_t Space = L' ';

    //        if (Mask == NewCell)
    //        {
    //            continue;
    //        }

    //        if (NewCell == EMPTY_CHAR)
    //        {
    //            continue;
    //        }

    //        ECharSpace NewCellSpace = GetCharSpace(NewCell);
    //        ECharSpace OldCellSpace = GetCharSpace(OldCell);

    //        if (OldCellSpace == ECharSpace::Empty && NewCellSpace == ECharSpace::TwoSpace)
    //        {
    //            if (GetCharSpace(NextCell) == ECharSpace::TwoSpace)
    //            {
    //                PrevCell = Space;
    //                OldCell = NewCell;
    //                NextCell = EMPTY_CHAR;
    //                NextNextCell = Space;
    //            }
    //            else // if(GetCharSpace(NextCell) == ECharSpace::OneSpace)
    //            {
    //                PrevCell = Space;
    //                OldCell = NewCell;
    //                NextCell = EMPTY_CHAR;
    //            }
    //        }
    //        else if (OldCellSpace == ECharSpace::TwoSpace && NewCellSpace == ECharSpace::OneSpace)
    //        {
    //            OldCell = NewCell;
    //            NextCell = Space;
    //        }
    //        else if (OldCellSpace == ECharSpace::Empty && NewCellSpace == ECharSpace::OneSpace)
    //        {
    //            PrevCell = Space;
    //            OldCell = NewCell;
    //        }
    //        else if (OldCellSpace == ECharSpace::OneSpace && NewCellSpace == ECharSpace::TwoSpace)
    //        {
    //            if (GetCharSpace(NextCell) == ECharSpace::TwoSpace)
    //            {
    //                OldCell = NewCell;
    //                NextCell = EMPTY_CHAR;
    //                NextNextCell = Space;
    //            }
    //            else // if(GetCharSpace(NextCell) == ECharSpace::OneSpace)
    //            {
    //                OldCell = NewCell;
    //                NextCell = EMPTY_CHAR;
    //            }
    //        }
    //    }
    //}

    for (int i = 1; i < LayerCount; ++i)
    {
        if (LayerList[i]->GetIsHiding())
        {
            continue;
        }

        const std::wstring& Layer = LayerList[i]->GetLayer();

        wchar_t Mask = LayerList[i]->GetMask();

        for (int j = 0; j < CombinedLayerSize; ++j)
        {
            const wchar_t NewCell = Layer[j];

            if (Mask == NewCell)
            {
                continue;
            }

            CombinedLayer[j] = NewCell;
        }
    }

    for (auto& C : CombinedLayer)
    {
        if (C == EmptyChar)
        {
            continue;
        }

        ScreenUI += C;
    }
}

RenderingHandler::~RenderingHandler()
{
}
