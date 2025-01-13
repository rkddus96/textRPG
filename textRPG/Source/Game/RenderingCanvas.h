#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "LogicHelper.h"
#include "ConstantContainer.h"

class RenderingLayer;

class RenderingCanvas
{
private:

	enum class ECharSpace
	{
		Empty,
		OneSpace,
		TwoSpace,
	};

public:

	RenderingCanvas();

	//RenderingCanvas(const RenderingCanvas& Other);

	void PrintCurrentScreenUI();
	void AddLayer(std::shared_ptr<RenderingLayer> NewLayerMask);
	void RemoveLayer(int LayerId);
	std::shared_ptr<RenderingLayer> GetRenderingLayer(int LayerId);

	void Clear();

	~RenderingCanvas();

private:

	void SortLayerInOrder();
	void CombineLayers();

	bool IsHangulOrHanJa(wchar_t WChar) const
	{
		return (LogicHelper::IsHangul(WChar) || LogicHelper::IsHanja(WChar));
	}

	ECharSpace GetCharSpace(wchar_t WChar) const
	{
		if (WChar == UI::EMPTY_CHAR)
		{
			return ECharSpace::Empty;
		}

		return (IsHangulOrHanJa(WChar)) ? ECharSpace::TwoSpace : ECharSpace::OneSpace;
	}

private:

	std::vector<std::shared_ptr<RenderingLayer>> LayerList;

	std::wstring ScreenUI;
};