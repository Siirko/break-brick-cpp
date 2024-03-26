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
            if (isColisionCircleRect(ball, paddle))
            {
                ball.bounce(angleOfLine(ball.getX(), ball.getY(), paddle.x + paddle.w / 2, paddle.y + paddle.h / 2));
                return true;
            }
        }
        else if (entity1.getType() == Collidable::CollidableType::BALL &&
                 entity2.getType() == Collidable::CollidableType::BRICK)
        {
            auto &ball = dynamic_cast<Ball &>(entity1);
            auto &brick = dynamic_cast<Brick &>(entity2);
            auto rect = brick.getRect();
            if (isColisionCircleRect(ball, rect))
            {
                ball.bounce(angleOfLine(ball.getX(), ball.getY(), rect.x + rect.w / 2, rect.y + rect.h / 2));
                brick.decreaseLife();
                return true;
            }
        }
        return false;
    }
};