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