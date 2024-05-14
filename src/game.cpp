#include "game.hpp"
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

Game::Game(const std::string &title, const int width, const int height, const std::shared_ptr<Paddle> &paddle,
           const std::vector<std::shared_ptr<Brick>> &bricks, const std::shared_ptr<Ball> &ball,
           const ColisionSolver &solveColision, int lives, std::function<void()> reset_lvl)
    : Window(title, width, height), m_paddle(paddle), m_bricks(bricks), m_ball(ball), m_solveColision(solveColision),
      m_background_color(Color::GRAY), m_lives(lives), m_bonusManager(width), m_balls(),
      m_reset_lvl(std::move(reset_lvl))
{
}

Game::~Game() {}

void Game::handleEvents(SDL_Event &event, const double delta)
{
    while (SDL_PollEvent(&event))
    {
        this->pollEvents(event);
        m_paddle->pollEvents(event);
    }
    m_paddle->applyEvents(delta);
}

void Game::pollEvents(SDL_Event &event)
{
    switch (event.type)
    {
    case SDL_QUIT:
        m_closed = true;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            m_closed = true;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void Game::clear()
{
    SDL_SetRenderDrawColor(this->m_renderer.get(), m_background_color.r, m_background_color.g, m_background_color.b,
                           m_background_color.a);
    SDL_RenderClear(this->m_renderer.get());
}

void Game::render(double delta)
{
    m_paddle->render(*m_renderer);
    m_ball->render(*m_renderer);
    for (auto &ball : m_balls)
        if (!ball->isOut())
            ball->render(*m_renderer);
    for (auto &brick : m_bricks)
        if (!brick->isDestroyed())
            brick->render(*m_renderer);
    for (auto &bonus : m_bonusManager.getBonuses())
        if (!bonus->isOut())
            bonus->render(*m_renderer);
}

void Game::update(double delta)
{
    // sloppy fix when loading a new lvl, it goes in it super fast
    // so player lost one life
    static bool restarting = false;
    if (restarting)
    {
        restarting = false;
        return;
    }
    if (m_bricks.empty())
    {
        std::cout << "You win! Going to next level..." << std::endl;
        m_reset_lvl();
        restarting = true;
        return;
    }

    else if (m_ball->isOut())
    {
        bool isGameOver = this->decreaseLives();
        std::cout << *this;
        if (isGameOver)
        {
            m_closed = true;
            std::cout << "Game Over!" << std::endl;
        }
        else
            m_ball->reset(m_width / 2, m_height / 2 + 25);
    }

    // random bonus
    m_bonusManager.generateRandomBonus(delta);

    m_solveColision.isColision(*m_ball, *m_paddle);

    m_ball->bounceWindow(m_width, m_height);
    m_ball->move(delta);

    m_balls.erase(std::remove_if(m_balls.begin(), m_balls.end(), [](const auto &ball) { return ball->isOut(); }),
                  m_balls.end());

    for (auto &ball : m_balls)
    {
        if (ball->isOut())
            continue;
        m_solveColision.isColision(*ball, *m_paddle);
        ball->bounceWindow(m_width, m_height);
        ball->move(delta);
    }

    m_bricks.erase(
        std::remove_if(m_bricks.begin(), m_bricks.end(), [](const auto &brick) { return brick->isDestroyed(); }),
        m_bricks.end());

    for (auto &brick : m_bricks)
    {
        if (brick->isDestroyed())
            continue;
        if (m_solveColision.isColision(*m_ball, *brick))
            brick->decreaseLife();
        for (auto &ball : m_balls)
            if (!ball->isOut() && m_solveColision.isColision(*ball, *brick))
                brick->decreaseLife();
    }

    m_bonusManager.getBonuses().erase(std::remove_if(m_bonusManager.getBonuses().begin(),
                                                     m_bonusManager.getBonuses().end(),
                                                     [&](const auto &bonus) { return bonus->isOut(); }),
                                      m_bonusManager.getBonuses().end());

    for (auto &bonus : m_bonusManager.getBonuses())
    {
        if (bonus->isOut())
            continue;
        bonus->move(delta);
        if (m_solveColision.isColision(*bonus, *m_paddle))
            bonus->result(*this);
    }
}

std::ostream &operator<<(std::ostream &os, const Game &game)
{
    os << "Bricks: " << game.m_bricks.size() << std::endl;
    os << "Lives: " << game.m_lives << std::endl;
    return os;
}