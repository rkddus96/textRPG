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

    // Getters
    string GetName() const { return name; }
    int GetMaxHp() const { return MaxHp; }
    int GetCurHp() const { return CurHp; }
    int GetPower() const { return Power; }
    int GetDefense() const { return Defense; }
    int GetExp() const { return Exp; }
    int GetMoney() const { return Money; }

    // Setters
    void SetName(const string& newName) { name = newName; }
    void SetMaxHp(int maxHp) { MaxHp = maxHp; }
    void SetCurHp(int curHp) { CurHp = curHp; }
    void SetPower(int power) { Power = power; }
    void SetDefense(int defense) { Defense = defense; }
    void SetExp(int exp) { Exp = exp; }
    void SetMoney(int money) { Money = money; }



protected:
    string name;
    int MaxHp, CurHp, Power, Defense, Exp, Money;
    

};

