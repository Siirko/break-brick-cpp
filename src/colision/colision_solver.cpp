#include "colision/colision_solver.hpp"

#include <algorithm>

bool ColisionSolver::isColisionCircle(Circle &circle1, Circle &circle2)
{
    int dx = circle1.getX() - circle2.getX();
    int dy = circle1.getY() - circle2.getY();
    int distance = sqrt(dx * dx + dy * dy);
    return distance < circle1.getRadius() + circle2.getRadius();
}

bool ColisionSolver::isColisionRect(SDL_Rect &rect1, SDL_Rect &rect2)
{
    return rect1.x < rect2.x + rect2.w && rect1.x + rect1.w > rect2.x && rect1.y < rect2.y + rect2.h &&
           rect1.y + rect1.h > rect2.y;
}

double distanceSquared(int x1, int y1, int x2, int y2)
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    return deltaX * deltaX + deltaY * deltaY;
}

bool ColisionSolver::isColisionCircleRect(Circle &circle, SDL_Rect &rect)
{
    int closestX, closestY;
    // Find closest x offset
    if (circle.getX() < rect.x)
    {
        closestX = rect.x;
    }
    else if (circle.getX() > rect.x + rect.w)
    {
        closestX = rect.x + rect.w;
    }
    else
    {
        closestX = circle.getX();
    }

    // Find closest y offset
    if (circle.getY() < rect.y)
    {
        closestY = rect.y;
    }
    else if (circle.getY() > rect.y + rect.h)
    {
        closestY = rect.y + rect.h;
    }
    else
    {
        closestY = circle.getY();
    }

    // If the closest point is inside the circle
    if (distanceSquared(circle.getX(), circle.getY(), closestX, closestY) < circle.getRadius() * circle.getRadius())
        return true;

    return false;
}

bool ColisionSolver::isColision(Ball &ball, Brick &brick)
{
    if (isColisionCircleRect(ball, brick))
    {
        ball.bounceBrick(brick);
        return true;
    }
    return false;
}

bool ColisionSolver::isColision(Ball &ball, Paddle &paddle)
{
    if (isColisionCircleRect(ball, paddle))
    {
        ball.bouncePaddle(paddle.getRect().x + paddle.getRect().w / 2, paddle.getRect().w);
        return true;
    }
    return false;
}