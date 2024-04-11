#include "entity/brick.hpp"
#include <random>

Brick::Brick(int x, int y, int width, int height, BrickType type)
    : m_width(width), m_height(height), m_position(Vector2f(x, y)), m_type(type), m_rect({x, y, width, height})
{
    m_life = m_type;
    m_color = brickTypeMap[m_type];
}

Brick::~Brick() {}

void Brick::render(SDL_Renderer &renderer) const
{
    if (m_destroyed)
        return;
    int res = SDL_SetRenderDrawColor(&renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    checkSDL<int>(res, res == 0);
    res = SDL_RenderFillRect(&renderer, &m_rect);
    checkSDL<int>(res, res == 0);
}

void Brick::decreaseLife()
{
    if (m_life > 0)
    {
        m_color.a = m_color.a / m_life;
        m_life--;
    }
    if (m_life == 0)
        m_destroyed = true;
}

std::ostream &operator<<(std::ostream &os, const Brick &brick)
{
    os << "Brick [x=" << brick.m_position.x << ", y=" << brick.m_position.y << ", width=" << brick.m_width
       << ", height=" << brick.m_height << ", life=" << brick.m_life << ", destroyed=" << brick.m_destroyed << "]";
    return os;
}