#pragma once
#include <SDL2/SDL.h>

class Circle
{
  protected:
    float m_x, m_y;
    int m_radius;

  public:
    Circle(const float x, const float y, const int radius);
    ~Circle();
    void drawCircle(SDL_Renderer &renderer, const int x, const int y, const int radius);
    void drawFilledCircle(SDL_Renderer &renderer, const int x, const int y, const int radius);
    const inline int getX() const { return m_x; }
    const inline int getY() const { return m_y; }
    const inline int getRadius() const { return m_radius; }
};