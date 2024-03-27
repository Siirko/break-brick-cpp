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

static inline double angleOfLine(const double x1, const double y1, const double x2, const double y2)
{
    double res_angle = atan2(abs(y2 - y1), abs(x2 - x1));
    // std::cout << fmt::format("coordinate of ball: ({}, {})\ncoordinate of paddle: ({}, {})\nangle: {}\n", x1, y1, x2,
    //                          y2, res_angle)
    //           << std::endl;
    // convert radian to degree
    res_angle = res_angle * 180 / M_PI;
    return res_angle;
}
