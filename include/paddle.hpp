#pragma once
#include "collidable.hpp"
#include "color.hpp"
#include "utils.hpp"
#include <SDL2/SDL.h>
#include <memory>
class Paddle : public Collidable
{
  private:
    SDL_Rect paddle;
    int m_speed;
    Color m_color;

  public:
    Paddle(const int x, const int y, const int width, const int height, const int speed);
    ~Paddle();

    inline bool collidesWindow(const int windowWidth, const int windowHeight) const;
    void moveLeft(const double delta);
    void moveRight(const double delta);
    void render(SDL_Renderer &renderer);
};