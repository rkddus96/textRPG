#pragma once
#include "Job.h"

class Warrior : public Job
{
public:
	// Warrior의 각 능력치 가중치
	float GetPowerWeight() const override { return 1.2f; }
	float GetDefenseWeight() const override { return 1.0f; }
	float GetLuckWeight() const override { return 0.8f; }
	
	const char* GetJobName() const override { return "Warrior"; }
};