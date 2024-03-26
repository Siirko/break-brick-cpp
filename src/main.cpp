#include "game.hpp"
#include <cstdio>
int main(int argc, char const *argv[])
{
    Game game("Breakout", 800, 600);
    while (!game.isClosed())
        game.loop();
    return 0;
}
