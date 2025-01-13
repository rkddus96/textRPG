#ifndef GOBLIN_H
#define GOBLIN_H

#include "Monster.h"

class Goblin : public Monster
{
public:
    Goblin();
    void DisplayIntroduction() override;
};


# endif