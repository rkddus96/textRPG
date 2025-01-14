#pragma once

#include <iostream>
#include <vector>
#include <unordered_set>
#include "ConstantContainer.h"

// 한글이나 한자처럼 두 자리 차지하는 문자는 가장 위쪽에 그려야 한다. 즉 LayerOrder가 가장 높아야 한다..
// 그리고 RenderingHanlder에서 가강 처음으로 그려지는 Layer는 숨기기 불가
class RenderingLayer
{
public:

	//RenderingLayer(int InLayerOrder, char InMask = ' ');
	RenderingLayer(int InLayerOrder, wchar_t InMask = UI::EMPTY_CHAR);

	// 레이어를 공백상태로 비움. 무슨 문자로 채울 지 결정 가능
	void ClearLayerFor(wchar_t CellWChar);

	// 레이어 출력하기
	void PrintCurrentLayer();

	// 사각형 그려줌
	void DrawRectanlge(int PositionX, int PositionY, int Width, int Height);

	/// <summary>
	/// 한글이나 한자는 한 글자당 두 칸 차지하므로 바로 연달아서 작성 불가.
	/// 필요할 경우 한 칸 띄우고 작성해야함.
	/// </summary>
	void DrawWCharacter(int PositionX, int PositionY, wchar_t WChar);

	/// <summary>
	/// 한글이나 한자는 한 글자당 두 칸 차지하므로 바로 연달아서 작성 불가.
	/// 필요할 경우 한 칸 띄우고 작성해야함.
	/// 한 문장에서 연달아서 쓰는건 가능.
	/// </summary>
	void DrawString(int PositionX, int PositionY, const std::string& Str, wchar_t Mask = L'\u200B');

	/// <summary>
	/// 한글이나 한자는 한 글자당 두 칸 차지하므로 바로 연달아서 작성 불가.
	/// 필요할 경우 한 칸 띄우고 작성해야함.
	/// 한 문장에서 연달아서 쓰는건 가능.
	/// </summary>
	void DrawString(int PositionX, int PositionY, const std::wstring& NewWString, wchar_t MaskWChar = L'\u200B');

	void DrawSurface(int StartPositionX, int StartPositionY, const std::vector<std::wstring>& Surface, wchar_t MaskWChar = L'\u200B');

	int GetLayerOrder() const
	{
		return LayerOrder;
	}

	const std::wstring& GetLayer() const
	{
		return Layer;
	}

	wchar_t GetMask() const
	{
		return Mask;
	}

	void SetMask(wchar_t NewMask)
	{
		Mask = NewMask;
	}

	

	bool operator == (const RenderingLayer& Other) const
	{
		return (LayerId == Other.LayerId);
	}

	void CombineUiLines();

	int GetLayerId() const
	{
		return LayerId;
	}

	bool GetIsHiding() const
	{
		return bIsHiding;
	}

	void SetIsHiding(bool bShouldHide)
	{
		bIsHiding = bShouldHide;
	}

	~RenderingLayer();

private:

	void InitLayer();

private:

	std::vector<std::wstring> UILines;
	std::wstring Layer;
	std::wstring FreeViewLayer;

	int LayerOrder;
	wchar_t Mask;

	int LayerId;

	bool bIsHiding;

	static std::unordered_set<int> LayerIdSet;
};