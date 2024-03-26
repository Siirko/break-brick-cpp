#pragma once
#include "color.hpp"
#include "utils.hpp"
#include <SDL2/SDL.h>
#include <map>
// use dictionary order

class Brick
{
  public:
    enum BrickType
    {
        NORMAL = 1,
        HARD,
        HARDENED,
        UNBREAKABLE,
    };

  private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    Color m_color;
    BrickType m_type;

  public:
    Brick(int x, int y, int width, int height, Color color, BrickType type);
    ~Brick();

    void render(SDL_Renderer &renderer) const;
};