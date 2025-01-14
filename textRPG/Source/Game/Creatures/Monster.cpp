#include "Monster.h"

Monster::Monster(const string& name, int baseHp, int basePower, int baseDefense, int exp, int money, int level)
    : Name(name), BaseHp(baseHp), BasePower(basePower), BaseDefense(baseDefense), Exp(exp), Money(money), Level(level) {
     
}

void Monster::CalculateStats(int hpModifier, int powerModifier, int defenseModifier, int expModifier, int moneyModifier)
{
    MaxHp = BaseHp + (hpModifier * Level);
    Power = BasePower + (powerModifier * Level); 
    Defense = BaseDefense + (defenseModifier * Level); 
    Exp += expModifier * Level;
    Money += moneyModifier * Level;

    CurHp = MaxHp; 
}

int Monster::TakeDamage(int rawDamage)
{
    int damage = rawDamage - Defense;
    if (damage < 0)
        damage = 0;

    CurHp -= damage;
    if (CurHp < 0)
        CurHp = 0;

    return damage;
}

bool Monster::IsDead()
{
    return CurHp <= 0;
}

