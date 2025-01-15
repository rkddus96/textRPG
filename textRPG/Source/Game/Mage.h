#pragma once
#include "IJob.h"

class Mage : public IJob
{
public:
	int GetPowerWeight() const override { return 3; }
	int GetDefenseWeight() const override { return 3; }
	int GetLuckWeight() const override { return  0; }
	int GetJobNum() const override { return 2; }

	std::wstring GetJobName() const override { return L"Mage"; }
};