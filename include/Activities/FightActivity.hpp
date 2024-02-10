#ifndef FIGHTACTIVITY_HPP
#define FIGHTACTIVITY_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Activities/Activity.hpp"
#include "GameState.hpp"
#include "ActivityEnum.hpp"
#include "Activities/MenuActivity.hpp"

class FightActivity: public Activity {
  private:
    std::string nameEnemy = "Enemy";

    sf::Texture background;
    sf::Texture gear;

  public:
    FightActivity();
  
    void displayActivity(GameState &gameState) override;
};

#endif