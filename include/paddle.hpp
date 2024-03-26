#pragma once

#include "color.hpp"
#include "utils.hpp"
#include <SDL2/SDL.h>
#include <memory>
class Paddle
{
  private:
    SDL_Rect paddle;
    int m_speed;
    Color m_color;

  public:
    Paddle(const int x, const int y, const int width, const int height, const int speed);
    ~Paddle();

    void moveLeft(const double delta);
    void moveRight(const double delta);
    void render(SDL_Renderer &renderer) const;
};