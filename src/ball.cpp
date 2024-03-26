#include "ball.hpp"
#include "utils.hpp"

Ball::Ball(const int x, const int y, const int radius, const int speed, Color color)
    : Collidable(), m_x(x), m_y(y), m_radius(radius), m_speed(speed), m_color(color)
{
}

void Ball::move(const double delta)
{
    m_x += m_speed;
    m_y += m_speed;
}

void Ball::render(SDL_Renderer &renderer)
{
    int res = SDL_SetRenderDrawColor(&renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    checkSDL<int>(res, res == 0);
    res = SDL_RenderFillCircle(renderer, m_x, m_y, m_radius);
    checkSDL<int>(res, res == 0);
}