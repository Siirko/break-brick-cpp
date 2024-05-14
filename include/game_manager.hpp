#pragma once
#include "brick_manager.hpp"
#include "entity/ball.hpp"
#include "entity/brick.hpp"
#include "entity/paddle.hpp"
#include "game.hpp"
#include <random>

class GameManager
{
  private:
    struct InitValues
    {
        int paddle_x, paddle_y, paddle_width, paddle_height;
        int ball_x, ball_y, ball_radius;
        float ball_speed, paddle_speed;
        int lifes;
        int margin_brick;
    };
    struct InitValues m_initValues;
    std::shared_ptr<Game> m_game;
    std::vector<std::string> m_levels;
    BrickManager m_brickManager;

    std::shared_ptr<Ball> generateBall(const float x, const float y, const int radius, float ball_speed);
    void retrieveLevels();

  public:
    GameManager(int width, int height, float ball_speed = .5f, float paddle_speed = .65f, int lifes = 3,
                int spawn_bonus_interval = 3)
    {
        init(width, height, ball_speed, paddle_speed, lifes, spawn_bonus_interval);
    }
    void init(int width, int height, float ball_speed, float paddle_speed, int lifes, int spawn_bonus_interval);
    void reset();
    inline std::shared_ptr<Game> getGame() const { return m_game; }
    inline std::string getNextLevel()
    {
        auto res = m_levels.front();
        m_levels.erase(m_levels.begin());
        return res;
    }
};