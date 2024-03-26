#pragma once
#include "collidable.hpp"
#include "color.hpp"
#include <SDL2/SDL.h>
class Ball : public Collidable
{
  private:
    int m_x, m_y, m_radius, m_speed;
    Color m_color;

  public:
    Ball(const int x, const int y, const int radius, const int speed, Color color = Color(Color::WHITE));
    void move(const double delta);
    void render(SDL_Renderer &renderer);
};