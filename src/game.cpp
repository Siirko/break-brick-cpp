#include "game.hpp"
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

Game::Game(const std::string &title, const int width, const int height, const std::shared_ptr<Paddle> &paddle,
           const std::vector<std::shared_ptr<Brick>> &bricks, const std::shared_ptr<Ball> &ball,
           const SolveColision &solveColision)
    : Window(title, width, height), m_paddle(paddle), m_bricks(bricks), m_ball(ball), m_solveColision(solveColision)
{
}

Game::~Game() {}

void Game::handleEvents(SDL_Event &event, const double delta)
{
    if (SDL_PollEvent(&event))
    {
        this->pollEvents(event, delta);
        m_paddle->pollEvents(event, delta);
    }
}

void Game::pollEvents(SDL_Event &event, const double delta)
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
{ // for black background
    SDL_SetRenderDrawColor(this->m_renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(this->m_renderer.get());
}

void Game::render(double delta)
{

    // for pink paddle
    m_paddle->render(*m_renderer);
    // for units to be displayed
    m_solveColision.isColision(*m_ball, *m_paddle);
    m_ball->render(*m_renderer);
    m_bricks.erase(
        std::remove_if(m_bricks.begin(), m_bricks.end(), [](const auto &brick) { return brick->isDestroyed(); }),
        m_bricks.end());
    // check colision with bricks and render them
    for (auto &brick : m_bricks)
    {
        if (brick->isDestroyed())
            continue;
        m_solveColision.isColision(*m_ball, *brick);
        brick->render(*m_renderer);
    }
    // for ball to move
    m_ball->move(delta);
    SDL_RenderPresent(m_renderer.get());
}
