#include "MonstserFactoryManager.h"


MonstserFactoryManager::MonstserFactoryManager()
{
    RegisterFactory("Slime", make_unique<SlimeFactory>());
    RegisterFactory("Orc", make_unique<OrcFactory>());
    RegisterFactory("Witch", make_unique<WitchFactory>());
    RegisterFactory("Goblin", make_unique<GoblinFactory>());
}

void MonstserFactoryManager::RegisterFactory(const string& type, unique_ptr<MonsterFactory> factory)
{
    Factories[type] = move(factory);
}


unique_ptr<Monster> MonstserFactoryManager::CreateMonster(const string& type) const
{
    auto it = Factories.find(type);
    if (it != Factories.end()) {

        return it->second->Create();
    }

    throw std::runtime_error("Monster type not found: " + type);
}

unique_ptr<Monster> MonstserFactoryManager::CreateMonster(const string& type, int level) const
{
    auto it = Factories.find(type);
    if (it != Factories.end()) {

        return it->second->Create(level);
    }

    throw std::runtime_error("Monster type not found: " + type);
}


unique_ptr<Monster> MonstserFactoryManager::CreateRandomMonster(int level) const
{
    
    srand(static_cast<unsigned int>(time(nullptr))); 
    int randomIndex = rand() % Factories.size();

    auto it = Factories.begin();
    advance(it, randomIndex); 

    return it->second->Create(level); 
}