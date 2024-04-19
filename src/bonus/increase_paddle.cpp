#include "entity/bonus/increase_paddle.hpp"
#include "game.hpp"
#include "utils.hpp"

IncreasePaddle::IncreasePaddle(const float x, const float y, const int radius, const float velocity_y)
    : Circle(x, y, radius), Bonus(BonusType::INCR_PADDLE), m_velocity_y(velocity_y), m_width_increase(10)
{
}

void IncreasePaddle::move(const double delta)
{
    // bonus is moving down
    m_position.y += m_velocity_y * delta;
}

void IncreasePaddle::render(SDL_Renderer &renderer)
{
    int res = SDL_SetRenderDrawColor(&renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    checkSDL<int>(res, res == 0);
    this->drawFilledCircle(renderer);
    int width, height;
    SDL_GetRendererOutputSize(&renderer, &width, &height);
    if (m_position.y > height)
        m_out = true;
}

void IncreasePaddle::result(Game &game)
{
    game.increasePaddleWidth(m_width_increase);
    m_out = true;
}