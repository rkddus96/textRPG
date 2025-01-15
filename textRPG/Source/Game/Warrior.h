#pragma once
#include "IJob.h"

class Warrior : public IJob
{

public:
	// Warrior의 각 능력치 가중치
	int GetPowerWeight() const override { return 5; }
	int GetDefenseWeight() const override { return 1; }
	int GetLuckWeight() const override { return 0; }
	int GetJobNum() const override { return 1; }
	
	std::wstring GetJobName() const override { return L"Warrior"; }
};