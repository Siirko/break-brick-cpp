#include "entity/bonus/bonus_manager.hpp"
#include "entity/bonus/extra_life.hpp"
#include "entity/bonus/increase_paddle.hpp"
#include "entity/bonus/multi_ball.hpp"

BonusManager::BonusManager(int width, int spawn_bonus_interval) : m_width(width), m_interval(spawn_bonus_interval)
{
    m_bonusFactory.addBonusFactory<ExtraLife>(Bonus::EXTRA_LIFE);
    m_bonusFactory.addBonusFactory<IncreasePaddle>(Bonus::INCR_PADDLE);
    m_bonusFactory.addBonusFactory<MultiBall>(Bonus::MULTI_BALL);
}

void BonusManager::addBonus(std::shared_ptr<Bonus> &bonus) { m_bonuses.push_back(bonus); }

void BonusManager::generateRandomBonus(const double delta)
{
    // each m_interval seconds generate a bonus
    static double time = 0;
    time += delta / 1000;
    if (time >= 3)
    {
        std::cout << "Generating bonus" << std::endl;
        time = 0;
        int x = m_gen() % m_width;
        int y = 0;
        int radius = 10;
        float velocity_y = .12f;
        std::uniform_int_distribution<int> dist(1, Bonus::BonusType::TOTAL_ITEMS - 1);
        Bonus::BonusType type = static_cast<Bonus::BonusType>(dist(m_gen));
        std::shared_ptr<Bonus> bonus = m_bonusFactory.bonusFactory[type](x, y, radius, velocity_y);
        if (bonus != nullptr)
            addBonus(bonus);
    }
}