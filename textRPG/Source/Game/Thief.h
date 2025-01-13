#pragma once
#include "Job.h"

class Thief : public Job
{
public:
	float GetPowerWeight() const override { return 1.0f; }
	float GetDefenseWeight() const override { return 0.8f; }
	float GetLuckWeight() const override { return 1.2f; }

	std::wstring GetJobName() const override { return L"Thief"; }
};
