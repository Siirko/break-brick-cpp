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
    template <typename T, typename U> bool isColision(T &entity1, U &entity2)
    {
        if (entity1.getType() == Collidable::CollidableType::BALL &&
            entity2.getType() == Collidable::CollidableType::PADDLE)
        {
            auto &ball = dynamic_cast<Ball &>(entity1);
            auto paddle = dynamic_cast<Paddle &>(entity2).getRect();
            return isColisionCircleRect(ball, paddle);
        }
        else if (entity1.getType() == Collidable::CollidableType::BALL &&
                 entity2.getType() == Collidable::CollidableType::BRICK)
        {
            auto &ball = dynamic_cast<Ball &>(entity1);
            auto brick = dynamic_cast<Brick &>(entity2).getRect();
            return isColisionCircleRect(ball, brick);
        }
        return false;
    }
};