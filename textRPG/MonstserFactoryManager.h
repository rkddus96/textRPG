#ifndef MONSTER_FACTORY_MANAGER_H
#define MONSTER_FACTORY_MANAGER_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include "./Source/Game/MonsterFactory.h"

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
    // 팩토리를 등록하는 함수
    void RegisterFactory(const string& type, unique_ptr<MonsterFactory> factory);

    // 등록된 팩토리로부터 몬스터를 생성하는 함수
    unique_ptr<Monster> createMonster(const string& type) const;

};

#endif
