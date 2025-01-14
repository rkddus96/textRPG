#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
#include "../AssetHandler.h"
#include "../Managers/GameManager.h"

using namespace std;

class Monster
{
public:
    virtual ~Monster() = default;
    virtual void DisplayIntroduction() = 0;
    int TakeDamage(int rawDamage);
    bool IsDead();

    // Getters
    string GetName() const { return Name; }
    int GetMaxHp() const { return MaxHp; }
    int GetCurHp() const { return CurHp; }
    int GetPower() const { return Power; }
    int GetDefense() const { return Defense; }
    int GetExp() const { return Exp; }
    int GetMoney() const { return Money; }

    // Setters
    void SetName(const string& newName) { Name = newName; }
    void SetMaxHp(int maxHp) { MaxHp = maxHp; }
    void SetCurHp(int curHp) { CurHp = curHp; }
    void SetPower(int power) { Power = power; }
    void SetDefense(int defense) { Defense = defense; }
    void SetExp(int exp) { Exp = exp; }
    void SetMoney(int money) { Money = money; }



protected:
    Monster(const string& name, int baseHp, int basePower, int baseDefense, int exp, int money, int level);

    void CalculateStats(int hpModifier, int powerModifier, int defenseModifier, int expModifier, int moneyModifier);

    string Name;
    int BaseHp, BasePower, BaseDefense; // 기본 능력치
    int MaxHp, CurHp, Power, Defense;   // 레벨 기반 능력치
    int Exp, Money, Level;
    
    FASKIIArtContainer MonsterImage;
};

