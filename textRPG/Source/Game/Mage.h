#pragma once
#include "Job.h"

class Mage : public Job
{
public:
	float GetPowerWeight() const override { return 0.8f; }
	float GetDefenseWeight() const override { return 1.2f; }
	float GetLuckWeight() const override { return 1.0f; }

	std::wstring GetJobName() const override { return L"Mage"; }
};