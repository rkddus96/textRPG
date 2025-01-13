#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>

using namespace std;

class Monster
{
public:
    virtual ~Monster() = default;
    virtual void DisplayIntroduction() = 0;
    void TakeDamage(int power);
    bool IsDead();

protected:
    string name;
    int MaxHp, CurHp, Power, Defense, Exp, Money;
    

};

