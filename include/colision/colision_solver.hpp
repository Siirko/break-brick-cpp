#pragma once

#include "entity/ball.hpp"
#include "entity/brick.hpp"
#include "entity/paddle.hpp"
#include "primitive/circle.hpp"
#include "window.hpp"
#include <SDL2/SDL.h>

struct Bonus;
class ColisionSolver
{
  private:
    bool isColisionCircle(Circle &circle1, Circle &circle2);
    bool isColisionRect(SDL_Rect &rect1, SDL_Rect &rect2);
    bool isColisionCircleRect(Circle &circle, SDL_Rect &rect);

  public:
    bool isColision(Ball &ball, Brick &brick);
    bool isColision(Ball &ball, Paddle &paddle);
    bool isColision(Bonus &bonus, Paddle &paddle);
};