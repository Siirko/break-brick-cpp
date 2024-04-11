#pragma once

#include "entity/ball.hpp"
#include "entity/brick.hpp"
#include "entity/paddle.hpp"
#include "primitive/circle.hpp"
#include "window.hpp"
#include <SDL2/SDL.h>

class SolveColision
{
  private:
    bool isColisionCircle(Circle &circle1, Circle &circle2);
    bool isColisionRect(SDL_Rect &rect1, SDL_Rect &rect2);
    bool isColisionCircleRect(Circle &circle, SDL_Rect &rect);

  public:
    inline bool isColision(Ball &ball, Brick &brick)
    {
        if (isColisionCircleRect(ball, brick))
        {
            ball.bounceBrick(brick);
            return true;
        }
        return false;
    }

    inline bool isColision(Ball &ball, Paddle &paddle)
    {
        if (isColisionCircleRect(ball, paddle))
        {
            ball.bouncePaddle(paddle.getRect().x + paddle.getRect().w / 2, paddle.getRect().w);
            return true;
        }
        return false;
    }
};