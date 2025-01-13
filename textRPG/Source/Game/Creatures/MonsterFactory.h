#ifndef MONSTERFACTORY_H
#define MONSTERFACTORY_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include "Monster.h" 

using namespace std;

class Monster;
class Slime;
class Orc;
class Witch;
class Goblin;

class MonsterFactory
{
public:
    virtual ~MonsterFactory() = default;
    virtual unique_ptr<Monster> Create() const = 0;
};

class SlimeFactory : public MonsterFactory
{
public:
    unique_ptr<Monster> Create() const override;
};

class OrcFactory : public MonsterFactory
{
public:
    unique_ptr<Monster> Create() const override;
};

class WitchFactory : public MonsterFactory
{
public:
    unique_ptr<Monster> Create() const override;
};

class GoblinFactory : public MonsterFactory
{
public:
    unique_ptr<Monster> Create() const override;
};

#endif