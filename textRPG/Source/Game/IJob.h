#pragma once

#include <string>

class IJob
{
public:
	virtual ~IJob() = default;

	// 순수 가상함수
	virtual float GetPowerWeight() const = 0;
	virtual float GetDefenseWeight() const = 0;
	virtual float GetLuckWeight() const = 0;
	virtual std::wstring GetJobName() const = 0;
};