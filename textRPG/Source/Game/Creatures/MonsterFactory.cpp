#include "MonsterFactory.h"
#include "Slime.h"
#include "Orc.h"
#include "Witch.h"
#include "Goblin.h"

unique_ptr<Monster> SlimeFactory::Create() const
{
    return make_unique<Slime>(1);
}

unique_ptr<Monster> SlimeFactory::Create(int level) const
{
    return make_unique<Slime>(level);
}

unique_ptr<Monster> OrcFactory::Create() const
{
    return make_unique<Orc>(1);
}

unique_ptr<Monster> OrcFactory::Create(int level) const
{
    return make_unique<Orc>(level);
}

unique_ptr<Monster> WitchFactory::Create() const
{
    return make_unique<Witch>(1);
}

unique_ptr<Monster> WitchFactory::Create(int level) const
{
    return make_unique<Witch>(level);
}

unique_ptr<Monster> GoblinFactory::Create() const
{
    return make_unique<Goblin>(1);
}

unique_ptr<Monster> GoblinFactory::Create(int level) const
{
    return make_unique<Goblin>(level);
}