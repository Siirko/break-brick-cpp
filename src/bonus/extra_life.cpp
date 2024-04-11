#include "entity/bonus/extra_life.hpp"
#include "game.hpp"
#include "utils.hpp"

ExtraLife::ExtraLife(const float x, const float y, const int radius, const float velocity_x, const float velocity_y,
                     const float speed)
    : Circle(x, y, radius), Bonus(BonusType::EXTRA_LIFE), m_velocity_x(velocity_x), m_velocity_y(velocity_y),
      m_speed(speed)
{
}

void ExtraLife::move(const double delta)
{
    // bonus is moving down
    m_position.y += m_velocity_y * delta;
}

void ExtraLife::render(SDL_Renderer &renderer)
{
    int res = SDL_SetRenderDrawColor(&renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    checkSDL<int>(res, res == 0);
    this->drawFilledCircle(renderer);
}

void ExtraLife::result(Game &game)
{
    game.increaseLives();
    m_out = true;
}