#include "colision/solve_colision.hpp"
#include "color.hpp"
#include "entity/brick.hpp"
#include "game.hpp"
#include "game_manager.hpp"
#include <cstdio>
#include <memory>
#include <random>
#include <vector>

int main(int argc, char const *argv[])
{
    const int width = 800, height = 600;
    const float ball_speed = .5f, paddle_speed = .65f;
    int lifes = 3;
    const GameManager gameManager(width, height, ball_speed, paddle_speed, lifes);
    auto game = gameManager.getGame();
    while (!game->isClosed())
        game->loop();
    return 0;
}
