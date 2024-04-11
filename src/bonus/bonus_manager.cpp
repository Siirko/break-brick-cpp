#include "entity/bonus/bonus_manager.hpp"
#include "entity/bonus/extra_life.hpp"

void BonusManager::addBonus(std::shared_ptr<Bonus> &bonus) { m_bonuses.push_back(bonus); }

void BonusManager::generateRandomBonus(const double delta)
{
    // each 10 seconds generate a new bonus
    static double time = 0;
    time += delta / 1000;
    if (time >= 10)
    {
        std::cout << "Generating bonus" << std::endl;
        time = 0;
        int x = 800 / 2;
        int y = 0;
        int radius = 10;
        float velocity_x = 0;
        float velocity_y = .12f;
        float speed = .12f;
        std::shared_ptr<Bonus> bonus = std::make_shared<ExtraLife>(x, y, radius, velocity_x, velocity_y, speed);
        addBonus(bonus);
    }
}