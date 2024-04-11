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

  public:
    BonusManager() { m_gen = std::mt19937(std::random_device()()); }
    void generateRandomBonus(const double delta);
    inline std::vector<std::shared_ptr<Bonus>> &getBonuses() { return m_bonuses; }
};