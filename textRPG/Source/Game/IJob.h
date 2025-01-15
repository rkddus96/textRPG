#pragma once

#include <string>

class IJob
{
public:
	virtual ~IJob() = default;

	// 순수 가상함수
	virtual int GetPowerWeight() const = 0;
	virtual int GetDefenseWeight() const = 0;
	virtual int GetLuckWeight() const = 0;
	virtual int GetJobNum() const = 0;
	virtual std::wstring GetJobName() const = 0;
};