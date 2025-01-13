#include "MonsterFactory.h"
#include "Slime.h"
#include "Orc.h"
#include "Witch.h"
#include "Goblin.h"

unique_ptr<Monster> SlimeFactory::Create() const
{
    return make_unique<Slime>();
}

unique_ptr<Monster> OrcFactory::Create() const
{
    return make_unique<Orc>();
}

unique_ptr<Monster> WitchFactory::Create() const
{
    return make_unique<Witch>();
}

unique_ptr<Monster> GoblinFactory::Create() const
{
    return make_unique<Goblin>();
}
