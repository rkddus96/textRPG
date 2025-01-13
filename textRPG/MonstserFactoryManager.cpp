#include "MonstserFactoryManager.h"



void MonstserFactoryManager::RegisterFactory(const string& type, unique_ptr<MonsterFactory> factory)
{
    Factories[type] = move(factory);
}

unique_ptr<Monster> MonstserFactoryManager::createMonster(const string& type) const
{
    auto it = Factories.find(type);
    if (it != Factories.end()) {
        // 팩토리를 통해 몬스터 생성
        return it->second->Create();
    }
    // 타입이 등록되지 않은 경우 예외를 던짐
    throw std::runtime_error("Monster type not found: " + type);
}
