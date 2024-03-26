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
        TOTAL_ITEMS
    };

  private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    // default value
    Color m_color = Color(Color::WHITE);
    BrickType m_type;
    SDL_Rect m_rect;
    int m_life;
    bool m_destroyed;

  public:
    Brick(int x, int y, int width, int height, BrickType type);
    ~Brick();

    void render(SDL_Renderer &renderer) const;
};