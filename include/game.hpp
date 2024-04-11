#pragma once
#include "colision/colision_solver.hpp"
#include "entity/ball.hpp"
#include "entity/brick.hpp"
#include "entity/paddle.hpp"
#include "window.hpp"
#include <memory>
#include <vector>
class Game : public Window, public Event
{
  private:
    std::shared_ptr<Paddle> m_paddle;
    std::vector<std::shared_ptr<Brick>> m_bricks;
    std::shared_ptr<Ball> m_ball;
    ColisionSolver m_solveColision;
    Color m_background_color;
    int m_lives;

  public:
    Game(const std::string &title, const int width, const int height, const std::shared_ptr<Paddle> &padle,
         const std::vector<std::shared_ptr<Brick>> &bricks, const std::shared_ptr<Ball> &ball,
         const ColisionSolver &solveColision, int lives);
    virtual ~Game();

    void handleEvents(SDL_Event &event, const double delta) override;
    void pollEvents(SDL_Event &event) override;
    void clear() override;
    void render(double delta) override;
    void update(double delta) override;
    inline bool decreaseLives()
    {
        if (m_lives > 0)
            m_lives--;
        return m_lives == 0;
    }
};