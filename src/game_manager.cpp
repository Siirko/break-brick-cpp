#include "game_manager.hpp"
#include <random>

void GameManager::init(int width, int height)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    int rows = 10;
    int columns = 5;
    int brick_width = 80;
    int brick_height = 40;
    generateBricks(rows, columns, brick_width, brick_height, gen);
    generateBall(width / 2, height / 2, 10, gen);
    std::shared_ptr<Paddle> paddle = std::make_shared<Paddle>(width / 2 - 50, height - 40, 80, 20, 10);
    m_game = std::make_shared<Game>("Breakout", width, height, paddle, m_bricks, m_ball, m_solveColision);
}

void GameManager::generateBricks(const int rows, const int columns, const int width, const int height, std::mt19937 gen)
{
    std::uniform_int_distribution<int> dis(1, static_cast<int>(Brick::BrickType::TOTAL_ITEMS) - 1);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            int random_number = dis(gen);
            m_bricks.push_back(std::make_shared<Brick>(i * width, j * height, width, height,
                                                       static_cast<Brick::BrickType>(random_number)));
        }
    }
}

void GameManager::generateBall(const float x, const float y, const int radius, std::mt19937 gen)
{
    // generate random velocity for calculating an random
    // angle for the ball
    std::uniform_real_distribution<float> dis_angle(0.0f, 2 * M_PI);
    // generate random angle
    float angle = dis_angle(gen);
    // calculate x and y velocity
    float velocity_x = cos(angle) * 0.05f;
    float velocity_y = sin(angle) * 0.05f;
    m_ball = std::make_shared<Ball>(x, y, radius, velocity_x, velocity_y);
}