#pragma once
#include <SDL2/SDL.h>
#include <cstdint>
#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <iostream>
#include <memory>

// macro to check if SDL is initialized
template <typename T> inline void checkSDL(const T &result, const T &error)
{
    if (result == error)
    {
        std::cout << fmt::format("Failed to initialize SDL: %s", SDL_GetError()) << std::endl;
        throw std::runtime_error("Failed to initialize SDL");
    }
}

static int SDL_RenderDrawCircle(SDL_Renderer &renderer, int x, int y, int radius)
{
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

    return status;
}

static int SDL_RenderFillCircle(SDL_Renderer &renderer, int x, int y, int radius)
{
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

    return status;
}