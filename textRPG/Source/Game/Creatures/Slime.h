#ifndef SLIME_H
#define SLIME_H

#include "Monster.h"

class Slime : public Monster
{
public:
    Slime(int level);
    void DisplayIntroduction() override;
};


# endif