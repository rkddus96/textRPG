#ifndef MONSTER_FACTORY_MANAGER_H
#define MONSTER_FACTORY_MANAGER_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include "MonsterFactory.h"
#include <cstdlib> // For rand and srand
#include <ctime>   // For time

using namespace std;

enum class EMonsterType
{
    Slime,
    Orc,
    Witch,
    Goblin,
    King,
    Devil

};


class MonstserFactoryManager
{
public:
    MonstserFactoryManager();
    unordered_map<EMonsterType, unique_ptr<MonsterFactory>> Factories;


public:

    void RegisterFactory(EMonsterType type, unique_ptr<MonsterFactory> factory);

    unique_ptr<Monster> CreateMonster(EMonsterType type) const;
    unique_ptr<Monster> CreateMonster(EMonsterType type, int level) const;
    unique_ptr<Monster> CreateRandomMonster(int level) const;

};

#endif
