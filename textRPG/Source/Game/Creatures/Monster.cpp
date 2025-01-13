#include "Monster.h"

Monster::Monster(const string& name, int baseHp, int basePower, int baseDefense, int exp, int money, int level)
    : name(name), BaseHp(baseHp), BasePower(basePower), BaseDefense(baseDefense), Exp(exp), Money(money), Level(level) {
     
}

void Monster::CalculateStats(int hpModifier, int powerModifier, int defenseModifier)
{
    MaxHp = static_cast<int>(BaseHp + (hpModifier * Level));
    Power = static_cast<int>(BasePower + (powerModifier * Level)); 
    Defense = static_cast<int>(BaseDefense + (defenseModifier * Level)); 
    CurHp = MaxHp; 
}

void Monster::TakeDamage(int rawDamage)
{
    int damage = rawDamage - Defense;
    if (damage < 0)
        damage = 0;

    CurHp -= damage;
    if (CurHp < 0)
        CurHp = 0;

}

bool Monster::IsDead()
{

    return CurHp <= 0;
}

