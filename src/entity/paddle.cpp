#include "entity/paddle.hpp"

Paddle::Paddle(const int x, const int y, const int width, const int height, const float speed)
    : Collidable(CollidableType::PADDLE), m_paddle{x, y, width, height}, m_speed(speed), m_color(Color::YELLOW),
      m_position(Vector2f(x, y))
{
}

Paddle::~Paddle() {}

void Paddle::moveLeft(const double delta)
{
    m_paddle.x += -m_speed * delta;
    m_position.x = m_paddle.x;
}

void Paddle::moveRight(const double delta)
{
    m_paddle.x += m_speed * delta;
    m_position.x = m_paddle.x;
}

void Paddle::render(SDL_Renderer &renderer)
{
    int res = SDL_SetRenderDrawColor(&renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    checkSDL<int>(res, res == 0);
    res = SDL_RenderFillRect(&renderer, &m_paddle);
    checkSDL<int>(res, res == 0);
    int width, height;
    SDL_GetRendererOutputSize(&renderer, &width, &height);
    if (!isWindowColliding(m_paddle.x, m_paddle.y, m_paddle.w, m_paddle.h, width, height))
    {
        if (m_paddle.x < 0)
        {
            this->m_paddle.x = 0;
            m_position.x = 0;
        }
        else if (m_paddle.x + m_paddle.w > width)
        {
            m_paddle.x = width - m_paddle.w;
            m_position.x = width - m_paddle.w;
        }
    }
}

void Paddle::pollEvents(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
        keyMap[event.key.keysym.sym] = true;
    else if (event.type == SDL_KEYUP && event.key.repeat == 0)
        keyMap[event.key.keysym.sym] = false;
}

void Paddle::applyEvents(const double delta)
{
    if (keyMap[SDLK_RIGHT])
        moveRight(delta);
    else if (keyMap[SDLK_LEFT])
        moveLeft(delta);
}