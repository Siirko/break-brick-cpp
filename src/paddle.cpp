#include "paddle.hpp"

Paddle::Paddle(const int x, const int y, const int width, const int height, const int speed)
    : Collidable(), paddle{x, y, width, height}, m_speed(speed), m_color(Color::YELLOW)
{
}

Paddle::~Paddle() {}

inline bool Paddle::collidesWindow(const int windowWidth, const int windowHeight) const
{
    return paddle.x >= 0 && paddle.x + paddle.w <= windowWidth;
}

void Paddle::moveLeft(const double delta) { this->paddle.x -= this->m_speed; }

void Paddle::moveRight(const double delta) { this->paddle.x += this->m_speed; }

void Paddle::render(SDL_Renderer &renderer)
{
    int res = SDL_SetRenderDrawColor(&renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    checkSDL<int>(res, res == 0);
    res = SDL_RenderFillRect(&renderer, &paddle);
    checkSDL<int>(res, res == 0);
    int width, height;
    SDL_GetRendererOutputSize(&renderer, &width, &height);
    if (!collidesWindow(width, height))
    {
        if (paddle.x < 0)
            this->paddle.x = 0;
        else if (paddle.x + paddle.w > 800)
            paddle.x = 800 - paddle.w;
    }
}