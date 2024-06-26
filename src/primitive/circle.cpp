#include "primitive/circle.hpp"
#include "utils.hpp"
Circle::Circle(const float x, const float y, const int radius) : m_position(x, y), m_radius(radius) {}

Circle::~Circle() {}

void Circle::drawCircle(SDL_Renderer &renderer)
{
    int x = getX();
    int y = getY();
    int radius = getRadius();

    int offsetx, offsety, d;
    int status;

    // CHECK_RENDERER_MAGIC(renderer, -1);

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx)
    {
        status += SDL_RenderDrawPoint(&renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(&renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(&renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(&renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(&renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(&renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(&renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(&renderer, x - offsety, y - offsetx);

        if (status < 0)
        {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx)
        {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety))
        {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else
        {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
    checkSDL<int>(status, status == 0);
}

void Circle::drawFilledCircle(SDL_Renderer &renderer)
{
    int x = getX();
    int y = getY();
    int radius = getRadius();
    int offsetx, offsety, d;
    int status;

    // CHECK_RENDERER_MAGIC(renderer, -1);

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx)
    {

        status += SDL_RenderDrawLine(&renderer, x - offsety, y + offsetx, x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(&renderer, x - offsetx, y + offsety, x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(&renderer, x - offsetx, y - offsety, x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(&renderer, x - offsety, y - offsetx, x + offsety, y - offsetx);

        if (status < 0)
        {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx)
        {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety))
        {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else
        {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    checkSDL<int>(status, status == 0);
}