#pragma once
#include <cstdint>
#include <format>
#include <iostream>

class Color
{
  public:
    // add color before WHITE and BLACK
    enum ColorType
    {
        RED = 0xFF0000,
        GREEN = 0x00FF00,
        BLUE = 0x0000FF,
        YELLOW = 0xFFFF00,
        WHITE = 0xFFFFFF,
        BLACK = 0x000000,
    };
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    Color(uint64_t color) : r((color >> 16) & 0xFF), g((color >> 8) & 0xFF), b(color & 0xFF), a(0xFF) {}
};