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
        return {0, 0};
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

std::vector<std::shared_ptr<Brick>> BrickManager::generateBricks(int width, int height, int margin)
{
    std::vector<std::shared_ptr<Brick>> bricks;
    auto data = loadBricks("level1");
    int brick_width, brick_height;
    // bricks needs to fit in the screen and not intersect with middle of the screen
    brick_width = width / data.cols;
    brick_height = height / 2 / data.rows;
    for (int i = 0; i < data.rows; i++)
    {
        for (int j = 0; j < data.cols; j++)
        {
            bricks.push_back(std::make_shared<Brick>(j * brick_height, i * brick_width + margin, brick_height,
                                                     brick_width, data.bricks[i][j]));
        }
    }

    // bricks.push_back(std::make_shared<Brick>(j * brick_height, i * brick_width + margin, brick_height,
    //                                          brick_width, data.bricks[i][j]));
    return bricks;
}