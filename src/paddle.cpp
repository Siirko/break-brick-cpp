#include "paddle.hpp"

Paddle::Paddle(const int x, const int y, const int width, const int height, const int speed)
    : paddle{x, y, width, height}, m_speed(speed), m_color("FF00FF")
{
}

Paddle::~Paddle() {}

void Paddle::moveLeft(const double delta) { this->paddle.x -= this->m_speed; }

void Paddle::moveRight(const double delta) { this->paddle.x += this->m_speed; }

void Paddle::render(SDL_Renderer &renderer) const
{
    int res = SDL_SetRenderDrawColor(&renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    checkSDL<int>(res, res == 0);
    res = SDL_RenderFillRect(&renderer, &paddle);
    checkSDL<int>(res, res == 0);
}