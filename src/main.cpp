#include "window.hpp"
#include <cstdio>
int main(int argc, char const *argv[])
{

    Window window("Hello World", 800, 600);
    while (!window.isClosed())
        window.loop();
    return 0;
}
