#pragma once

#include "entity/bonus/bonus.hpp"
#include <memory>
#include <random>
#include <vector>

class BonusManager
{
  private:
    std::vector<std::shared_ptr<Bonus>> m_bonuses;
    std::mt19937 m_gen;
    void addBonus(std::shared_ptr<Bonus> &bonus);
    int m_width;
    int m_interval; // interval in seconds
    BonusFactory m_bonusFactory;

  public:
    BonusManager(int width, int spawn_bonus_interval = 10);

    void generateRandomBonus(const double delta);
    inline std::vector<std::shared_ptr<Bonus>> &getBonuses() { return m_bonuses; }
};