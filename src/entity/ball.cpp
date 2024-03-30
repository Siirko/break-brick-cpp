#include "entity/ball.hpp"
#include "utils.hpp"

Ball::Ball(const float x, const float y, const int radius, const float velocity_x, const float velocity_y,
           const float speed, Color color)
    : Circle(x, y, radius), Collidable(CollidableType::BALL), m_velocity_x(velocity_x), m_velocity_y(velocity_y),
      m_speed(speed), m_color(color)
{
}

void Ball::move(const double delta)
{
    m_position.x += m_velocity_x * delta;
    m_position.y += m_velocity_y * delta;
}

void Ball::bounceBrick(Vector2f brick)
{
    /*
    This is not good
    */
    float angle = atan2(m_position.y - brick.y, m_position.x - brick.x);
    m_velocity_x = m_speed * cos(angle);
    m_velocity_y = m_speed * sin(angle);
}

void Ball::bouncePaddle(float mid_x_paddle, float width_paddle)
{
    float ratio = (this->getX() - mid_x_paddle) / (width_paddle / 2);
    // max angle
    float angle = std::abs(ratio * (M_PI / 3));
    if (ratio < 0)
    {
        m_velocity_x = -m_speed * sin(angle);
        m_velocity_y = -m_speed * cos(angle);
    }
    else
    {
        m_velocity_x = m_speed * sin(angle);
        m_velocity_y = -m_speed * cos(angle);
    }
}

void Ball::bounceWindow(int width, int height)
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
}
