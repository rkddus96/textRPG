#include "Status.h"
#include <stdexcept> // 예외 처리를 위해 필요


Status::Status()
{
	stats[EStat::MaxHp] = 100;
	stats[EStat::MaxHp] = 100;
	stats[EStat::MaxHp] = 10;
	stats[EStat::MaxHp] = 10;
	stats[EStat::MaxHp] = 10;
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
	stats[statType] = value;

	// 스탯 변경 시 콜백 호출
	if (OnStatChanged)
	{
		OnStatChanged(statType, value);
	}
}

float Status::StatToDamage(float powerWeight, float defenseWeight, float luckWeight)
{
	// 입력한 가중치에 각 스탯을 곱한다.
	float power = static_cast<float>(GetStat(EStat::Power)) * powerWeight;
	float defense = static_cast<float>(GetStat(EStat::Defense)) * defenseWeight;
	float luck = static_cast<float>(GetStat(EStat::Luck)) * luckWeight;

	// Damage 계산 로직 => (power + luck ) + defense
	float damage = std::max(power + luck + defense, 0.0f);

	return damage;
	
}