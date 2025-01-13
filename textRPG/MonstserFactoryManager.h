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
    // ���丮�� ����ϴ� �Լ�
    void RegisterFactory(const string& type, unique_ptr<MonsterFactory> factory);

    // ��ϵ� ���丮�κ��� ���͸� �����ϴ� �Լ�
    unique_ptr<Monster> createMonster(const string& type) const;

};

#endif
