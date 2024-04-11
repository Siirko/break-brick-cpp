#pragma once

#include "color.hpp"
#include <SDL2/SDL.h>
#include <map>

struct Game;
struct BonusManager;
class Bonus
{
  public:
    enum BonusType
    {
        EXTRA_LIFE = 1,
        BIG_PADDLE,
        MULTI_BALL,
        TOTAL_ITEMS
    };

  protected:
    bool m_out = false;
    enum BonusType m_type;
    Color m_color;

  public:
    std::map<BonusType, Color::ColorType> bonusTypeMap = {{BonusType::EXTRA_LIFE, Color::CYAN},
                                                          {BonusType::BIG_PADDLE, Color::OLIVE},
                                                          {BonusType::MULTI_BALL, Color::PINK}};
    Bonus(enum BonusType type) : m_type(type) { m_color = Color(bonusTypeMap[type]); }
    virtual void result(Game &game) = 0;
    virtual void move(const double delta) = 0;
    virtual void render(SDL_Renderer &renderer) = 0;
    inline bool isOut() const { return m_out; }
    inline void setOut() { m_out = true; }
};