#pragma once
#include "colision/collidable.hpp"
#include "color.hpp"
#include "utils.hpp"
#include "vector2.hpp"
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

    std::map<BrickType, Color::ColorType> brickTypeMap = {{BrickType::NORMAL, Color::GREEN},
                                                          {BrickType::HARD, Color::YELLOW},
                                                          {BrickType::HARDENED, Color::ORANGE},
                                                          {BrickType::UNBREAKABLE, Color::RED}};

  private:
    int m_width;
    int m_height;
    Vector2f m_position;
    Color m_color = Color(Color::WHITE);
    BrickType m_type;
    SDL_Rect m_rect;
    int m_life;
    bool m_destroyed = false;

  public:
    Brick(int x, int y, int width, int height, BrickType type);
    ~Brick();
    void decreaseLife();
    inline bool isDestroyed() const { return m_destroyed; }
    const inline Vector2f &getPosition() const { return m_position; }
    void render(SDL_Renderer &renderer) const;
    inline SDL_Rect getRect() const { return m_rect; }
    operator SDL_Rect() const { return m_rect; }
    operator SDL_Rect &() { return m_rect; }
    friend std::ostream &operator<<(std::ostream &os, const Brick &brick);
};