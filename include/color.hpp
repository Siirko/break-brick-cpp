#pragma once
#include <cstdint>
#include <iostream>

class Color
{
  public:
    enum ColorType
    {
        RED = 0xFF0000,
        GREEN = 0x00FF00,
        BLUE = 0x0000FF,
        YELLOW = 0xFFFF00,
        WHITE = 0xFFFFFF,
        BLACK = 0x000000,
        ORANGE = 0xFFA500,
        GRAY = 0x3d3d3d,
        LIGHT_GRAY = 0x6b6b6b,
        DARK_GRAY = 0x292929,
        PURPLE = 0x800080,
        CYAN = 0x00FFFF,
        PINK = 0xFFC0CB,
        BROWN = 0xA52A2A,
        LIME = 0x00FF00,
        TEAL = 0x008080,
        INDIGO = 0x4B0082,
        MAROON = 0x800000,
        NAVY = 0x000080,
        OLIVE = 0x808000,
    };
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    Color() = default;
    Color(uint64_t color) : r((color >> 16) & 0xFF), g((color >> 8) & 0xFF), b(color & 0xFF), a(0xFF) {}
    Color(ColorType color) : r((color >> 16) & 0xFF), g((color >> 8) & 0xFF), b(color & 0xFF), a(0xFF) {}
};