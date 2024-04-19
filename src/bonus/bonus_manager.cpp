#include "entity/bonus/bonus_manager.hpp"
#include "entity/bonus/extra_life.hpp"

void BonusManager::addBonus(std::shared_ptr<Bonus> &bonus) { m_bonuses.push_back(bonus); }

void BonusManager::generateRandomBonus(const double delta)
{
    // each m_interval seconds generate a bonus
    static double time = 0;
    time += delta / 1000;
    if (time >= m_interval)
    {
        std::cout << "Generating bonus" << std::endl;
        time = 0;
        int x = m_gen() % m_width;
        int y = 0;
        int radius = 10;
        float velocity_y = .12f;
        std::shared_ptr<Bonus> bonus = std::make_shared<ExtraLife>(x, y, radius, velocity_y);
        addBonus(bonus);
    }
}