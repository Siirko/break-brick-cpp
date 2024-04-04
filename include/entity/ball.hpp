#pragma once
#include "colision/collidable.hpp"
#include "color.hpp"
#include "primitive/circle.hpp"
#include <SDL2/SDL.h>
class Ball : public Circle, public Collidable
{
  private:
    float m_velocity_x, m_velocity_y;
    float m_speed;
    Color m_color;

  public:
    Ball(const float x, const float y, const int radius, const float velocity_x, const float velocity_y,
         const float speed, Color color = Color::WHITE);
    const inline Vector2f &getPosition() const { return m_position; }
    void move(const double delta);
    void render(SDL_Renderer &renderer);
    void bounceBrick(SDL_Rect &brick, int ball_radius, int ball_x, int ball_y);
    void bouncePaddle(float mid_x_paddle, float width_paddle);
    void bounceWindow(int width, int height);
};