#pragma once
#include <SDL2/SDL.h>
#include <cstdint>
#include <format>
#include <iostream>

// macro to check if SDL is initialized
template <typename T> inline void checkSDL(const T &result, const T &error)
{
    if (result == error)
    {
        std::cout << std::format("Failed to initialize SDL: {}", SDL_GetError());
        throw std::runtime_error("Failed to initialize SDL");
    }
}

struct RGBA
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    RGBA(std::string color, uint8_t alpha = 255) : a(alpha)
    {
        try
        {
            r = std::stoi(color.substr(0, 2), nullptr, 16);
            g = std::stoi(color.substr(2, 2), nullptr, 16);
            b = std::stoi(color.substr(4, 2), nullptr, 16);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
};
