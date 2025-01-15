#ifndef KING_H
#define KING_H

#include "Monster.h"

class King : public Monster
{
public:
    King();
    void DisplayIntroduction() override;
};

# endif