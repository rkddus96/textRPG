#pragma once
#include "IJob.h"

class Warrior : public IJob
{
public:
	// Warrior의 각 능력치 가중치
	float GetPowerWeight() const override { return 1.2f; }
	float GetDefenseWeight() const override { return 1.0f; }
	float GetLuckWeight() const override { return 0.8f; }
	
	std::wstring GetJobName() const override { return L"Warrior"; }
};