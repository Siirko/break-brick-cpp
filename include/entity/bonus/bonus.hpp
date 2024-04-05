#pragma once

#include "colision/collidable.hpp"
#include "color.hpp"

class Bonus : public Collidable
{
  public:
    enum BonusType
    {
        EXTRA_LIFE = 1,
        BIG_PADDLE,
        MULTI_BALL,
        TOTAL_ITEMS
    };
};