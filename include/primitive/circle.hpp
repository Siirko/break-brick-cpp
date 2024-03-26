#pragma once
#include <SDL2/SDL.h>

class Circle
{
  protected:
    int m_x, m_y, m_radius;

  public:
    Circle(const int x, const int y, const int radius);
    ~Circle();
    void drawCircle(SDL_Renderer &renderer, const int x, const int y, const int radius);
    void drawFilledCircle(SDL_Renderer &renderer, const int x, const int y, const int radius);
    const inline int getX() const { return m_x; }
    const inline int getY() const { return m_y; }
    const inline int getRadius() const { return m_radius; }
};