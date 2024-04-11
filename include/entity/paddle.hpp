#pragma once
#include "color.hpp"
#include "event.hpp"
#include "utils.hpp"
#include "vector2.hpp"
#include <SDL2/SDL.h>
#include <memory>
class Paddle : public Event
{
  private:
    SDL_Rect m_paddle;
    float m_speed;
    Color m_color;

  public:
    Paddle(const int x, const int y, const int width, const int height, const float speed);
    virtual ~Paddle();

    void moveLeft(const double delta);
    void moveRight(const double delta);
    void render(SDL_Renderer &renderer);
    const inline SDL_Rect getRect() const { return m_paddle; }
    operator SDL_Rect() const { return m_paddle; }
    operator SDL_Rect &() { return m_paddle; }

    void pollEvents(SDL_Event &event) override;
    void applyEvents(const double delta) override;
};