#ifndef WITCH_H
#define WITCH_H

#include "Monster.h"

class Witch : public Monster
{
public:
    Witch(int level);
    void DisplayIntroduction() override;
};


# endif