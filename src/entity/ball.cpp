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
    m_position.x += m_velocity_x * m_speed * delta;
    m_position.y += m_velocity_y * m_speed * delta;
}

void Ball::bounceBrick(Vector2f brick)
{
    // simple rebond mirror
    if (m_position.x - m_radius < brick.x || m_position.x + m_radius > brick.x + brick.y)
        m_velocity_x = -m_velocity_x;
    if (m_position.y - m_radius < brick.y || m_position.y + m_radius > brick.y + brick.y)
        m_velocity_y = -m_velocity_y;
}

void Ball::bouncePaddle(Vector2f paddle)
{
    // https://stackoverflow.com/questions/573084/how-to-calculate-bounce-angle/64421233#64421233
    // still not right, multiple bounce with this method :(
    Vector2f angle = m_position.angleTo(paddle);
    Vector2f new_velocity = Vector2f(m_velocity_x, m_velocity_y).rotate(2 * angle.y);
    m_velocity_x = new_velocity.x;
    m_velocity_y = new_velocity.y;
    // static int count = 0;
    // std::cout << fmt::format("{}: {} {}\n", count++, angle.x, angle.y);
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
