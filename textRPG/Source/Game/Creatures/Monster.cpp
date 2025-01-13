#include "Monster.h"

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
