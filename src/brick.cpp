#include "brick.hpp"

Brick::Brick(int x, int y, int width, int height, Color color, BrickType type)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_color(color), m_type(type)
{
}

Brick::~Brick() {}