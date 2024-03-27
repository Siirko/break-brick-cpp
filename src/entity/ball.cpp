#include "entity/ball.hpp"
#include "utils.hpp"

Ball::Ball(const float x, const float y, const int radius, const float velocity_x, const float velocity_y, Color color)
    : Circle(x, y, radius), Collidable(CollidableType::BALL), m_velocity_x(velocity_x), m_velocity_y(velocity_y),
      m_color(color)
{
}

void Ball::move(const double delta)
{
    m_position.x += m_velocity_x;
    m_position.y += m_velocity_y;
}

void Ball::bounce(int x, int y)
{
    float paddle_angle = angleOfLine(m_position.x, m_position.y, x, y);
    // wall_angle is in degree, calculate the angle of the ball after bouncing
    float angle = 2 * paddle_angle - 180 - angleOfLine(0, 0, m_velocity_x, m_velocity_y);
    // convert degree to radian
    // angle = angle * M_PI / 180;
    m_velocity_x = cos(angle) * -0.05;
    m_velocity_y = sin(angle) * -0.05;
}

inline void Ball::bounceWindow(int width, int height)
{
    if (m_position.x - m_radius < 0 || m_position.x + m_radius > width)
        m_velocity_x = -m_velocity_x;
    if (m_position.y - m_radius < 0 || m_position.y + m_radius > height)
        m_velocity_y = -m_velocity_y;
}

void Ball::render(SDL_Renderer &renderer)
{
    int res = SDL_SetRenderDrawColor(&renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    checkSDL<int>(res, res == 0);
    drawFilledCircle(renderer);
    int width, height;
    SDL_GetRendererOutputSize(&renderer, &width, &height);
    bounceWindow(width, height);
}
