#include "MonstserFactoryManager.h"



void MonstserFactoryManager::RegisterFactory(const string& type, unique_ptr<MonsterFactory> factory)
{
    Factories[type] = move(factory);
}

unique_ptr<Monster> MonstserFactoryManager::createMonster(const string& type) const
{
    auto it = Factories.find(type);
    if (it != Factories.end()) {

        return it->second->Create();
    }

    throw std::runtime_error("Monster type not found: " + type);
}

unique_ptr<Monster> MonstserFactoryManager::createMonster(const string& type, int level) const
{
    auto it = Factories.find(type);
    if (it != Factories.end()) {

        return it->second->Create(level);
    }

    throw std::runtime_error("Monster type not found: " + type);
}
