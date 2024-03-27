#pragma once
#include "colision/collidable.hpp"
#include "color.hpp"
#include "event.hpp"
#include "utils.hpp"
#include "vector2.hpp"
#include <SDL2/SDL.h>
#include <memory>
class Paddle : public Collidable, public Event
{
  private:
    SDL_Rect m_paddle;
    float m_speed;
    Color m_color;
    Vector2f m_position;

  public:
    Paddle(const int x, const int y, const int width, const int height, const float speed);
    ~Paddle();

    void moveLeft(const double delta);
    void moveRight(const double delta);
    void render(SDL_Renderer &renderer);
    const inline SDL_Rect getRect() const { return m_paddle; }
    const inline Vector2f &getPosition() const { return m_position; }
    operator SDL_Rect() const { return m_paddle; }
    operator SDL_Rect &() { return m_paddle; }

    void pollEvents(SDL_Event &event) override;
    void applyEvents(const double delta) override;
};