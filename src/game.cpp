#include "game.hpp"
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

Game::Game(const std::string &title, const int width, const int height,
           const std::vector<std::shared_ptr<Brick>> &bricks, const std::shared_ptr<Ball> ball)
    : Window(title, width, height), m_paddle(std::make_unique<Paddle>(width / 2, height - 40, 80, 20, 10)),
      m_bricks(bricks), m_ball(ball)
{
}

Game::~Game() {}

void Game::pollEvents(SDL_Event &event, const double delta)
{
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            this->m_closed = true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                this->m_closed = true;
                break;
            case SDLK_LEFT:
                m_paddle->moveLeft(delta);
                break;
            case SDLK_RIGHT:
                m_paddle->moveRight(delta);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
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
    for (auto &brick : m_bricks)
        brick->render(*m_renderer);
    // for ball to be displayed
    m_ball->render(*m_renderer);
    // m_ball->move(delta);
    SDL_RenderPresent(m_renderer.get());
}