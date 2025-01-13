#ifndef ORC_H
#define ORC_H

#include "Monster.h"

class Orc : public Monster
{
public:
    Orc(int level);
    void DisplayIntroduction() override;
};


# endif