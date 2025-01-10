#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "LogicHelper.h"

class RenderingLayer;

class RenderingHandler
{
private:

	enum class ECharSpace
	{
		Empty,
		OneSpace,
		TwoSpace,
	};

public:

	RenderingHandler();

	void PrintCurrentScreenUI();
	void AddLayer(std::shared_ptr<RenderingLayer> NewLayerMask);
	void RemoveLayer(int LayerId);

	void Clear();

	~RenderingHandler();

private:

	void SortLayerInOrder();
	void CombineLayers();

	bool IsHangulOrHanJa(wchar_t WChar) const
	{
		return (LogicHelper::IsHangul(WChar) || LogicHelper::IsHanja(WChar));
	}

	ECharSpace GetCharSpace(wchar_t WChar) const
	{
		if (WChar == L'\u200B')
		{
			return ECharSpace::Empty;
		}

		return (IsHangulOrHanJa(WChar)) ? ECharSpace::TwoSpace : ECharSpace::OneSpace;
	}

private:

	std::vector<std::shared_ptr<RenderingLayer>> LayerList;

	std::wstring ScreenUI;
};