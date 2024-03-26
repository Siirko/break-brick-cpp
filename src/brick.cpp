#include "brick.hpp"
#include <random>

Brick::Brick(int x, int y, int width, int height, BrickType type)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_type(type), m_rect({m_x, m_y, m_width, m_height})
{
    std::cout << type << std::endl;
    switch (m_type)
    {
    case BrickType::NORMAL:
        m_color = Color(Color::RED);
        m_life = 1;
        break;
    case BrickType::HARD:
        m_color = Color(Color::GREEN);
        m_life = 2;
        break;
    case BrickType::HARDENED:
        m_color = Color(Color::BLUE);
        m_life = 3;
        break;
    case BrickType::UNBREAKABLE:
        m_color = Color(Color::YELLOW);
        m_life = -1;
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