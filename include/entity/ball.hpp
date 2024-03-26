#pragma once
#include "colision/collidable.hpp"
#include "color.hpp"
#include "primitive/circle.hpp"
#include <SDL2/SDL.h>
class Ball : public Circle, public Collidable
{
  private:
    int m_speed;
    Color m_color;

  public:
    Ball(const int x, const int y, const int radius, const int speed, Color color = Color(Color::WHITE));
    void move(const double delta);
    void render(SDL_Renderer &renderer);
};