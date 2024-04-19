#pragma once

#include "entity/bonus/bonus.hpp"
#include "primitive/circle.hpp"

class IncreasePaddle : public Circle, public Bonus
{
  private:
    float m_velocity_y;
    int m_width_increase;

  public:
    IncreasePaddle(const float x, const float y, const int radius, const float velocity_y);
    virtual ~IncreasePaddle() {}
    void result(Game &game) override;
    void move(const double delta) override;
    void render(SDL_Renderer &renderer) override;
};