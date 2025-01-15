#include "Status.h"
#include <stdexcept> // 예외 처리를 위해 필요


Status::Status()
{
	stats[EStat::MaxHp] = 100;
	stats[EStat::CurHp] = 100;
	stats[EStat::Power] = 10;
	stats[EStat::Defense] = 10;
	stats[EStat::Luck] = 10;
}

// auto의 자료형 std::unordered_map<EStat, int>::iterator
int Status::GetStat(EStat statType) const
{
	auto it = stats.find(statType);
	if (it != stats.end())
	{
		return it->second;
	}

	throw std::out_of_range("Stat not found: Invalid EStat value");
}

void Status::SetStat(EStat statType, int value)
{
	stats[statType] = std::max(value, 0);

	// 스탯 변경 시 콜백 호출
	if (OnStatChanged)
	{
		OnStatChanged(statType, stats[statType]);
	}
}

