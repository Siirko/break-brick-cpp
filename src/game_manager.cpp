#include "game_manager.hpp"
#include <random>

void GameManager::init(int width, int height, float ball_speed, float paddle_speed, int lifes, std::string level)
{
    m_initValues = {.paddle_x = width / 2 - 50,
                    .paddle_y = height - 40,
                    .paddle_width = 80,
                    .paddle_height = 5,
                    .ball_x = width / 2,
                    .ball_y = height / 2 + 25,
                    .ball_radius = 10,
                    .ball_speed = ball_speed,
                    .paddle_speed = paddle_speed,
                    .lifes = lifes,
                    .margin_brick = 10};
    std::random_device rd;
    std::mt19937 gen(rd());
    retrieveLevels();

    auto bricks = m_brickManager.generateBricks(width, height, 10, level);
    auto balls =
        generateBall(m_initValues.ball_x, m_initValues.ball_y, m_initValues.ball_radius, m_initValues.ball_speed);
    std::shared_ptr<Paddle> paddle =
        std::make_shared<Paddle>(m_initValues.paddle_x, m_initValues.paddle_y, m_initValues.paddle_width,
                                 m_initValues.paddle_height, m_initValues.paddle_speed);
    m_game = std::make_shared<Game>("Breakout", width, height, paddle, bricks, balls, ColisionSolver(), lifes,
                                    [&]() { reset(); });
}

void GameManager::reset()
{
    if (m_levels.empty())
        std::cout << "No more levels, you win!" << std::endl;
    std::cout << "Going to next level, generating ..." << std::endl;
    std::string level = m_levels.front();
    SDL_Delay(3000);
    m_game->clear();
    m_game->getBall()->reset(m_initValues.ball_x, m_initValues.ball_y);
    m_game->getBalls().clear();
    m_game->getBonusManager().getBonuses().clear();
    m_game->getPaddle()->reset(m_initValues.paddle_x, m_initValues.paddle_y, m_initValues.paddle_width,
                               m_initValues.paddle_height);
    m_game->getBricks().clear();
    m_game->getBricks() = m_brickManager.generateBricks(m_game->getWidth(), m_game->getHeight(), 10, level);
    m_game->setLife(m_initValues.lifes);
    std::cout << *m_game;
}

void GameManager::retrieveLevels()
{
    std::filesystem::path path = std::filesystem::current_path();
    path /= "assets/levels/";
    std::vector<std::string> levels;
    for (const auto &entry : std::filesystem::directory_iterator(path))
        levels.push_back(entry.path().filename());
    for (const auto &level : levels)
        std::cout << level << std::endl;
    m_levels = levels;
}

std::shared_ptr<Ball> GameManager::generateBall(const float x, const float y, const int radius, float ball_speed)
{
    float velocity_x = 0;
    float velocity_y = ball_speed;
    return std::make_shared<Ball>(x, y, radius, velocity_x, velocity_y, ball_speed);
}