#pragma once

#include "utils.hpp"
#include <SDL2/SDL.h>
#include <memory>
class Paddle
{
  private:
    SDL_Rect paddle;
    int m_speed;
    RGBA m_color;

  public:
    Paddle(const int x, const int y, const int width, const int height, const int speed);
    ~Paddle();

    inline int getX() const { return paddle.x; }
    inline int getY() const { return paddle.y; }
    inline int getWidth() const { return paddle.w; }
    inline int getHeight() const { return paddle.h; }
    inline int getSpeed() const { return m_speed; }

    void moveLeft(const double delta);
    void moveRight(const double delta);
    void render(SDL_Renderer &renderer) const;
};