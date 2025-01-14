#pragma once
#include "IJob.h"

class Thief : public IJob
{
public:
	int GetPowerWeight() const override { return 3; }
	int GetDefenseWeight() const override { return 1; }
	int GetLuckWeight() const override { return 7; }

	std::wstring GetJobName() const override { return L"Thief"; }
};
