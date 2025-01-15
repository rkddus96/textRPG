#include "MonstserFactoryManager.h"


MonstserFactoryManager::MonstserFactoryManager()
{
    RegisterFactory(EMonsterType::Slime, make_unique<SlimeFactory>());
    RegisterFactory(EMonsterType::Orc, make_unique<OrcFactory>());
    RegisterFactory(EMonsterType::Witch, make_unique<WitchFactory>());
    RegisterFactory(EMonsterType::Goblin, make_unique<GoblinFactory>());
    RegisterFactory(EMonsterType::King, make_unique<KingFactory>());
    RegisterFactory(EMonsterType::Devil, make_unique<DevilFactory>());
}

void MonstserFactoryManager::RegisterFactory(EMonsterType type, unique_ptr<MonsterFactory> factory)
{
    Factories[type] = move(factory);
}


unique_ptr<Monster> MonstserFactoryManager::CreateMonster(EMonsterType type) const
{
    auto it = Factories.find(type);
    if (it != Factories.end()) {

        return it->second->Create();
    }


}

unique_ptr<Monster> MonstserFactoryManager::CreateMonster(EMonsterType type, int level) const
{
    auto it = Factories.find(type);
    if (it != Factories.end()) {

        return it->second->Create(level);
    }


}


unique_ptr<Monster> MonstserFactoryManager::CreateRandomMonster(int level) const
{
    
    srand(static_cast<unsigned int>(time(nullptr)));
    int randomIndex = rand() % (Factories.size() - 2); // king과 devil 빼고 랜덤 생성

    auto it = Factories.begin();
    advance(it, randomIndex);

    return it->second->Create(level);
}