#pragma once

#include "collidable.hpp"
#include "entity/ball.hpp"
#include "entity/brick.hpp"
#include "entity/paddle.hpp"
#include "primitive/circle.hpp"
#include <SDL2/SDL.h>

class SolveColision
{
  private:
    bool isColisionCircle(Circle &circle1, Circle &circle2);
    bool isColisionRect(SDL_Rect &rect1, SDL_Rect &rect2);
    bool isColisionCircleRect(Circle &circle, SDL_Rect &rect);

  public:
    bool isColision(Collidable &entity1, Collidable &entity2);
};