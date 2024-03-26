#include "brick.hpp"
#include "color.hpp"
#include "game.hpp"
#include <cstdio>
#include <memory>
#include <random>
#include <vector>

int main(int argc, char const *argv[])
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, static_cast<int>(Brick::BrickType::TOTAL_ITEMS) - 1);

    std::vector<std::shared_ptr<Brick>> bricks;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            int random_number = dis(gen);
            bricks.push_back(
                std::make_shared<Brick>(i * 80, j * 40, 80, 40, static_cast<Brick::BrickType>(random_number)));
        }
    }
    Game game("Breakout", 800, 600, bricks);
    while (!game.isClosed())
        game.loop();
    return 0;
}
