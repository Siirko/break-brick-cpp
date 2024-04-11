#include "game_manager.hpp"
#include <random>

void GameManager::init(int width, int height, float ball_speed, float paddle_speed, int lifes)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    int rows = 10;
    int columns = 5;
    int brick_width = 80;
    int brick_height = 40;
    auto bricks = generateBricks(rows, columns, brick_width, brick_height, gen);
    auto balls = generateBall(width / 2, height / 2, 10, ball_speed);
    std::shared_ptr<Paddle> paddle = std::make_shared<Paddle>(width / 2 - 50, height - 40, 80, 5, paddle_speed);
    m_game = std::make_shared<Game>("Breakout", width, height, paddle, bricks, balls, ColisionSolver(), lifes);
}

std::vector<std::shared_ptr<Brick>> GameManager::generateBricks(const int rows, const int columns, const int width,
                                                                const int height, std::mt19937 gen)
{
    std::vector<std::shared_ptr<Brick>> bricks;
    std::uniform_int_distribution<int> dis(1, static_cast<int>(Brick::BrickType::TOTAL_ITEMS) - 1);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            int random_number = dis(gen);
            bricks.push_back(std::make_shared<Brick>(i * width, j * height, width, height,
                                                     static_cast<Brick::BrickType>(random_number)));
        }
    }
    return bricks;
}

std::shared_ptr<Ball> GameManager::generateBall(const float x, const float y, const int radius, float ball_speed)
{
    float velocity_x = 0;
    float velocity_y = ball_speed;
    return std::make_shared<Ball>(x, y, radius, velocity_x, velocity_y, ball_speed);
}