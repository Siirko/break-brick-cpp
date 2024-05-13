#include "brick_manager.hpp"
#include <fstream>

struct BrickManager::BrickData BrickManager::loadBricks(std::string level)
{
    // level file are represented as file containg
    // the number of rows and columns of the bricks
    // and the bricks themselves
    // example:
    // 12 3
    // HHHHHHHHHHH
    // HHHHHHHHHHH
    // NNNNNNNNNNN
    // For type of bricks:
    // N -> NormalBrick
    // H -> HardBrick
    // D -> HardenedBrick
    // U -> UnbreakableBrick

    std::filesystem::path path = std::filesystem::current_path();
    path /= "assets/levels/" + level;
    std::ifstream stream;
    stream.open(path);
    if (!stream.is_open())
    {
        std::cerr << "Error opening file: " << path << std::endl;
        std::throw_with_nested(std::runtime_error("Error opening file"));
    }
    // get the number of rows and columns
    int rows, cols;
    stream >> cols >> rows;

    std::vector<std::vector<Brick::BrickType>> bricks(rows, std::vector<Brick::BrickType>(cols));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            char brick;
            stream >> brick;
            // could be avoided if we had a constexpr map ...
            switch (brick)
            {
            case 'N':
                bricks[i][j] = Brick::BrickType::NORMAL;
                break;
            case 'H':
                bricks[i][j] = Brick::BrickType::HARD;
                break;
            case 'D':
                bricks[i][j] = Brick::BrickType::HARDENED;
                break;
            case 'U':
                bricks[i][j] = Brick::BrickType::UNBREAKABLE;
                break;
            default:
                bricks[i][j] = Brick::BrickType::NORMAL;
                break;
            }
        }
    }
    stream.close();
    return {rows, cols, bricks};
}

std::vector<std::shared_ptr<Brick>> BrickManager::generateBricks(int width, int height, int margin, std::string level)
{
    std::vector<std::shared_ptr<Brick>> bricks;
    auto data = loadBricks(level);

    int available_height = height / 2 - margin;

    int brick_height = available_height / data.rows;

    int brick_width = width / data.cols;

    for (int i = 0; i < data.rows; i++)
    {
        for (int j = 0; j < data.cols; j++)
        {
            int x = j * brick_width;
            int y = i * brick_height + margin;

            bricks.push_back(std::make_shared<Brick>(x, y, brick_width, brick_height, data.bricks[i][j]));
        }
    }

    return bricks;
}