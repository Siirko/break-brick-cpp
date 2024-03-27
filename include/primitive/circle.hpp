#pragma once
#include "vector2.hpp"
#include <SDL2/SDL.h>

class Circle
{
  protected:
    Vector2f m_position;
    int m_radius;

  public:
    Circle(const float x, const float y, const int radius);
    ~Circle();
    void drawCircle(SDL_Renderer &renderer);
    void drawFilledCircle(SDL_Renderer &renderer);
    const inline int getX() const { return m_position.x; }
    const inline int getY() const { return m_position.y; }
    const inline Vector2f &getPosition() const { return m_position; }
    const inline int getRadius() const { return m_radius; }
};