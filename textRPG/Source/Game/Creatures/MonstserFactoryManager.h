#ifndef MONSTER_FACTORY_MANAGER_H
#define MONSTER_FACTORY_MANAGER_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include "MonsterFactory.h"

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


class MonstserFactoryManager
{
public:
    unordered_map<string, unique_ptr<MonsterFactory>> Factories;


public:

    void RegisterFactory(const string& type, unique_ptr<MonsterFactory> factory);

    unique_ptr<Monster> createMonster(const string& type) const;

};

#endif
