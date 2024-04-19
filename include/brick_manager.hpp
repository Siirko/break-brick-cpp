#pragma once
#include "entity/brick.hpp"
#include <filesystem>
#include <memory>
#include <vector>

class BrickManager
{
  public:
    struct BrickData
    {
        int rows;
        int cols;
        std::vector<std::vector<Brick::BrickType>> bricks;
    };
    struct BrickData loadBricks(std::string level);
    std::vector<std::shared_ptr<Brick>> generateBricks(int width, int height, int margin);
};