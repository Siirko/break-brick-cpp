#include "game.hpp"
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

Game::Game(const std::string &title, const int width, const int height, const std::shared_ptr<Paddle> &paddle,
           const std::vector<std::shared_ptr<Brick>> &bricks, const std::shared_ptr<Ball> &ball,
           const SolveColision &solveColision)
    : Window(title, width, height), m_paddle(paddle), m_bricks(bricks), m_ball(ball), m_solveColision(solveColision),
      m_background_color(Color::GRAY)
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
    for (auto &brick : m_bricks)
        brick->render(*m_renderer);
}

void Game::update(double delta)
{
    m_solveColision.isColision(*m_ball, *m_paddle);

    m_ball->bounceWindow(m_width, m_height);
    m_ball->move(delta);

    m_bricks.erase(
        std::remove_if(m_bricks.begin(), m_bricks.end(), [](const auto &brick) { return brick->isDestroyed(); }),
        m_bricks.end());
    // check colision with bricks and render them
    for (auto &brick : m_bricks)
    {
        if (brick->isDestroyed())
            continue;
        if (m_solveColision.isColision(*m_ball, *brick))
            brick->decreaseLife();
    }
    SDL_RenderPresent(m_renderer.get());
}