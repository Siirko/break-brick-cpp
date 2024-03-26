#include "colision/solve_colision.hpp"
#include "colision/collidable.hpp"

#include <algorithm>

bool SolveColision::isColisionCircle(Circle &circle1, Circle &circle2)
{
    int dx = circle1.getX() - circle2.getX();
    int dy = circle1.getY() - circle2.getY();
    int distance = sqrt(dx * dx + dy * dy);
    return distance < circle1.getRadius() + circle2.getRadius();
}

bool SolveColision::isColisionRect(SDL_Rect &rect1, SDL_Rect &rect2)
{
    return rect1.x < rect2.x + rect2.w && rect1.x + rect1.w > rect2.x && rect1.y < rect2.y + rect2.h &&
           rect1.y + rect1.h > rect2.y;
}

bool SolveColision::isColisionCircleRect(Circle &circle, SDL_Rect &rect)
{
    int closestX = std::clamp(circle.getX(), rect.x, rect.x + rect.w);
    int closestY = std::clamp(circle.getY(), rect.y, rect.y + rect.h);
    int dx = circle.getX() - closestX;
    int dy = circle.getY() - closestY;
    return sqrt(dx * dx + dy * dy) < circle.getRadius();
}