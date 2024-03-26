#include "entity/brick.hpp"
#include <random>

Brick::Brick(int x, int y, int width, int height, BrickType type)
    : Collidable(CollidableType::BRICK), m_x(x), m_y(y), m_width(width), m_height(height), m_type(type),
      m_rect({m_x, m_y, m_width, m_height})
{
    m_life = m_type;
    switch (m_type)
    {
    case BrickType::NORMAL:
        m_color = Color(Color::RED);
        break;
    case BrickType::HARD:
        m_color = Color(Color::GREEN);
        break;
    case BrickType::HARDENED:
        m_color = Color(Color::BLUE);
        break;
    case BrickType::UNBREAKABLE:
        m_color = Color(Color::YELLOW);
        break;
    default:
        throw std::invalid_argument("Invalid brick type");
    }
}

Brick::~Brick() {}

void Brick::render(SDL_Renderer &renderer) const
{
    int res = SDL_SetRenderDrawColor(&renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    checkSDL<int>(res, res == 0);
    res = SDL_RenderFillRect(&renderer, &m_rect);
    checkSDL<int>(res, res == 0);
}

std::ostream &operator<<(std::ostream &os, const Brick &brick)
{
    os << "Brick [x=" << brick.m_x << ", y=" << brick.m_y << ", width=" << brick.m_width
       << ", height=" << brick.m_height << ", life=" << brick.m_life << ", destroyed=" << brick.m_destroyed << "]";
    return os;
}