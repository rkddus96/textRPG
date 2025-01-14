#ifndef MONSTER_FACTORY_MANAGER_H
#define MONSTER_FACTORY_MANAGER_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include "MonsterFactory.h"
#include <cstdlib> // For rand and srand
#include <ctime>   // For time

class Monster;
class Slime;
class Orc;
class Witch;
class Goblin;
class MonsterFactory;
class SlimeFactory;
class OrcFactory;
class WitchFactory;
class GoblinFactory;

using namespace std;

enum class EMonsterType
{
    Slime,
    Orc,
    Witch,
    Goblin
};


class MonstserFactoryManager
{
public:
    MonstserFactoryManager();
    unordered_map<string, unique_ptr<MonsterFactory>> Factories;


public:

    void RegisterFactory(const string& type, unique_ptr<MonsterFactory> factory);

    unique_ptr<Monster> CreateMonster(const string& type) const;
    unique_ptr<Monster> CreateMonster(const string& type, int level) const;
    unique_ptr<Monster> CreateRandomMonster(int level) const;

};

#endif
