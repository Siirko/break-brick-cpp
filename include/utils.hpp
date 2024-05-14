#pragma once
#include <SDL2/SDL.h>
#include <cstdint>
#if __has_include(<format>)
#include <format>
#endif
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
template <typename... Args> std::string string_format(const std::string &format, Args... args)
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
// if std::format is found in the code, use it
// else use string_format
#ifdef __cpp_lib_format
        throw std::runtime_error(std::format("SDL Error: {}", SDL_GetError()));
#else
        throw std::runtime_error(string_format("SDL Error: {}", SDL_GetError()));
#endif
    }
}