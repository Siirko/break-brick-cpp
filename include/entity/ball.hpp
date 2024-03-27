#pragma once
#include "colision/collidable.hpp"
#include "color.hpp"
#include "primitive/circle.hpp"
#include <SDL2/SDL.h>
class Ball : public Circle, public Collidable
{
  private:
    float m_velocity_x, m_velocity_y;
    Color m_color;

  public:
    Ball(const float x, const float y, const int radius, const float velocity_x, const float velocity_y,
         Color color = Color::WHITE);
    void move(const double delta);
    void render(SDL_Renderer &renderer);
    void bounce(int x, int y);
    inline void bounceWindow(int width, int height);
};