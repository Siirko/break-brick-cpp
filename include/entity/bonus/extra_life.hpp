#pragma once

#include "entity/bonus/bonus.hpp"
#include "primitive/circle.hpp"

class ExtraLife : public Circle, public Bonus
{
  private:
    float m_velocity_x;
    float m_velocity_y;
    float m_speed;

  public:
    ExtraLife(const float x, const float y, const int radius, const float velocity_x, const float velocity_y,
              const float speed);
    void result(Game &game) override;
    void move(const double delta) override;
    void render(SDL_Renderer &renderer) override;
};