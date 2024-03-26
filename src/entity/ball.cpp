#include "entity/ball.hpp"
#include "utils.hpp"

Ball::Ball(const float x, const float y, const int radius, const float velocity_x, const float velocity_y, Color color)
    : Circle(x, y, radius), Collidable(CollidableType::BALL), m_velocity_x(velocity_x), m_velocity_y(velocity_y),
      m_color(color)
{
}

void Ball::move(const double delta)
{
    m_x += m_velocity_x;
    m_y += m_velocity_y;
}

void Ball::bounce(float wall_angle)
{
    float angle = angleOfLine(m_x, m_y, m_x + m_velocity_x, m_y + m_velocity_y);
    float new_angle = 2 * wall_angle - angle;
    m_velocity_x = cos(new_angle) * 0.05;
    m_velocity_y = sin(new_angle) * 0.05;
}

void Ball::render(SDL_Renderer &renderer)
{
    int res = SDL_SetRenderDrawColor(&renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    checkSDL<int>(res, res == 0);
    drawFilledCircle(renderer, m_x, m_y, m_radius);
    int width, height;
    SDL_GetRendererOutputSize(&renderer, &width, &height);
    if (m_x - m_radius < 0 || m_x + m_radius > width)
    {
        m_velocity_x = -m_velocity_x;
    }
    if (m_y - m_radius < 0 || m_y + m_radius > height)
    {
        m_velocity_y = -m_velocity_y;
    }
}
