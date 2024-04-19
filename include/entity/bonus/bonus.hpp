#pragma once

#include "color.hpp"
#include <SDL2/SDL.h>
#include <functional>
#include <map>
#include <memory>

class Game;
class BonusManager;
class Bonus
{
  public:
    enum BonusType
    {
        EXTRA_LIFE = 1,
        INCR_PADDLE,
        MULTI_BALL,
        TOTAL_ITEMS
    };

  protected:
    bool m_out = false;
    enum BonusType m_type;
    Color m_color;

  public:
    std::map<BonusType, Color::ColorType> bonusTypeMap = {{BonusType::EXTRA_LIFE, Color::CYAN},
                                                          {BonusType::INCR_PADDLE, Color::OLIVE},
                                                          {BonusType::MULTI_BALL, Color::PINK}};

    Bonus(enum BonusType type) : m_type(type) { m_color = Color(bonusTypeMap[type]); }
    virtual void result(Game &game) = 0;
    virtual void move(const double delta) = 0;
    virtual void render(SDL_Renderer &renderer) = 0;
    inline bool isOut() const { return m_out; }
    inline void setOut() { m_out = true; }
};

class BonusFactory
{
  public:
    std::map<Bonus::BonusType, typename std::function<std::shared_ptr<Bonus>(int, int, int, float)>> bonusFactory;

    std::map<Bonus::BonusType, typename std::function<std::shared_ptr<Bonus>(int, int, int, float)>> &getBonusFactory()
    {
        return bonusFactory;
    }

    template <typename T> void addBonusFactory(Bonus::BonusType type) { bonusFactory[type] = createBonus<T>; }

    template <typename T> static std::shared_ptr<Bonus> createBonus(int x, int y, int radius, float velocity_y)
    {
        return std::make_shared<T>(x, y, radius, velocity_y);
    }
};