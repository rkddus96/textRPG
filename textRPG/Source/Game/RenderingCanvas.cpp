#include "RenderingCanvas.h"
#include "RenderingLayer.h"
#include <algorithm>
#include <Windows.h>

RenderingCanvas::RenderingCanvas() :
    ScreenUI(L"")
{
}

//RenderingCanvas::RenderingCanvas(const RenderingCanvas& Other): 
//    LayerList(Other.LayerList),
//    ScreenUI(Other.ScreenUI)
//{
//}

void RenderingCanvas::PrintCurrentScreenUI()
{
    if (LayerList.size() <= 0)
    {
        // 로그
        return;
    }

    CombineLayers();
    //ClearConsole();

    //HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들 얻기

    //DWORD Written;
    //WriteConsoleW(ConsoleHandle, ScreenUI.c_str() , (DWORD)ScreenUI.size(), &Written, nullptr); // 빠르게 콘솔에 출력
    LogicHelper::PrintWStringFast(ScreenUI);
}

void RenderingCanvas::AddLayer(std::shared_ptr<RenderingLayer> NewLayerMask)
{
    LayerList.push_back(NewLayerMask);
}

void RenderingCanvas::RemoveLayer(int LayerId)
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

std::shared_ptr<RenderingLayer> RenderingCanvas::GetRenderingLayer(int LayerId)
{
    if (LayerList.size() <= 0)
    {
        return nullptr;
    }

    auto It = std::find_if(LayerList.begin(), LayerList.end(), [&](std::shared_ptr<RenderingLayer> OtherLayer)->bool
        {
            if (OtherLayer == nullptr)
            {
                std::cout << "RenderingCanvas, GetRenderingLayer : OtherLayer is Null" << std::endl;
                return false;
            }

            return LayerId == OtherLayer->GetLayerId();
        });

    if (It == LayerList.end())
    {
        return nullptr;
    }

    return *It;
}

void RenderingCanvas::Clear()
{
    LayerList.resize(0);
}

void RenderingCanvas::SortLayerInOrder()
{
	std::stable_sort(LayerList.begin(), LayerList.end(), 
		[](std::shared_ptr<RenderingLayer> Layer1, std::shared_ptr<RenderingLayer> Layer2)->bool
		{
			return Layer1->GetLayerOrder() < Layer2->GetLayerOrder();
		});
}

void RenderingCanvas::CombineLayers()
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

    wchar_t EmptyChar = UI::EMPTY_CHAR;

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

RenderingCanvas::~RenderingCanvas()
{
}
