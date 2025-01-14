#ifndef DEVIL_H
#define DEVIL_H

#include "Monster.h"

class Devil : public Monster
{
public:
    Devil();
    void DisplayIntroduction() override;
};

# endif