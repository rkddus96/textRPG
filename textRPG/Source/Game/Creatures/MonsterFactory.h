#ifndef MONSTERFACTORY_H
#define MONSTERFACTORY_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include "Monster.h" 
#include "Slime.h"
#include "Orc.h"
#include "Witch.h"
#include "Goblin.h"
#include "King.h"
#include "Devil.h"

using namespace std;

class MonsterFactory
{
public:
    virtual ~MonsterFactory() = default;
    virtual unique_ptr<Monster> Create() const = 0;
    virtual unique_ptr<Monster> Create(int level) const = 0;
};

class SlimeFactory : public MonsterFactory
{
public:
    unique_ptr<Monster> Create() const override;

    unique_ptr<Monster> Create(int level) const override;
};

class OrcFactory : public MonsterFactory
{
public:
    unique_ptr<Monster> Create() const override;

    unique_ptr<Monster> Create(int level) const override;
};

class WitchFactory : public MonsterFactory
{
public:
    unique_ptr<Monster> Create() const override;

    unique_ptr<Monster> Create(int level) const override;
};

class GoblinFactory : public MonsterFactory
{
public:
    unique_ptr<Monster> Create() const override;

    unique_ptr<Monster> Create(int level) const override;
};

class KingFactory : public MonsterFactory
{
public:
    unique_ptr<Monster> Create() const override;

};

class DevilFactory : public MonsterFactory
{
public:
    unique_ptr<Monster> Create() const override;

};
#endif