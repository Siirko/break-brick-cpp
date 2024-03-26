#pragma once
#include "brick.hpp"
#include "paddle.hpp"
#include "window.hpp"

#include <memory>
#include <vector>
class Game : public Window
{
  private:
    std::unique_ptr<Paddle> m_paddle;
    std::vector<std::shared_ptr<Brick>> m_bricks;

  public:
    Game(const std::string &title, const int width, const int height,
         const std::vector<std::shared_ptr<Brick>> &bricks);
    ~Game();

    void pollEvents(SDL_Event &event, const double delta) override;
    void clear() override;
    void render(double delta) override;
};