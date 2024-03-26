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
    const int width = 800;
    const int height = 600;
    const GameManager gameManager(width, height);
    auto game = gameManager.getGame();
    while (!game->isClosed())
        game->loop();
    return 0;
}
