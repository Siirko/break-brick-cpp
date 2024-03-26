#pragma once
#include "colision/collidable.hpp"
#include "color.hpp"
#include "utils.hpp"
#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include <ostream>

class Brick : public Collidable
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
    bool m_destroyed = false;

  public:
    Brick(int x, int y, int width, int height, BrickType type);
    ~Brick();
    inline void decreaseLife()
    {
        if (m_life > 0)
            m_life--;
        if (m_life == 0)
            m_destroyed = true;
    }
    inline bool isDestroyed() const { return m_destroyed; }

    void render(SDL_Renderer &renderer) const;
    inline SDL_Rect getRect() const { return m_rect; }
    operator SDL_Rect() const { return m_rect; }
    operator SDL_Rect &() { return m_rect; }
    friend std::ostream &operator<<(std::ostream &os, const Brick &brick);
};