#pragma once
#include "paddle.hpp"
#include "window.hpp"

class Game : public Window
{
  private:
    std::unique_ptr<Paddle> m_paddle;

  public:
    Game(const std::string &title, const int width, const int height);
    ~Game();

    void pollEvents(SDL_Event &event, const double delta) override;
    void clear() override;
    void render(double delta) override;
};