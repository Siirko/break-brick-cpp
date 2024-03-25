#pragma once
#include <SDL2/SDL.h>
#include <cstdint>
#include <iostream>
#include <memory>

// using this way because apparently std::format is only available in gcc 13, and so some ubuntu versions
// don't have it yet
template <typename... Args> std::string str_format(const std::string &format, Args... args)
{
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
    if (size_s <= 0)
    {
        throw std::runtime_error("Error during formatting.");
    }
    auto size = static_cast<size_t>(size_s);
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

// macro to check if SDL is initialized
template <typename T> inline void checkSDL(const T &result, const T &error)
{
    if (result == error)
    {
        std::cout << str_format("Failed to initialize SDL: %s", SDL_GetError()) << std::endl;
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
