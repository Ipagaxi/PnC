#ifndef FIGHTACTIVITY_HPP
#define FIGHTACTIVITY_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Activities/Activity.hpp"
#include "ActivityEnum.hpp"
#include "UIComponents/UIPlayerStats.hpp"
#include "Activities/MenuActivity.hpp"
#include "UIElements/UIColorBox.hpp"
#include "UIElements/UIButton.hpp"
#include "UIElements/UIBox.hpp"
#include "Actors/Player.hpp"
#include "PerlinNoise.hpp"
#include "GameState.hpp"
#include "Defines.hpp"
#include "Actors/Enemy.hpp"

class FightActivity: public Activity {
  public:
    FightActivity(GameState &gameState);
  
    void executeActivity(GameState &gameState) override;
    void runFight(GameState &gameState);

  private:
    std::string nameEnemy = "Enemy";

    sf::Texture backgroundTX;
    sf::Sprite backgroundSP;
    UIButton exitButton = UIButton("buttonClose/buttonClose.png");

    UIColorBox colorBox = UIColorBox("colorPIC_gen.png", "border_color_square.png");
    sf::Text colorText;
    sf::Color pickedColor;
    UIPlayerStats playerStatsBox;

    Enemy enemy = Enemy("Zucchini?!?", 20, 5, {100, 190, 30}, "zucchini_damon.png", "colorPIC_1.png", "borderMetal.png");
    sf::Texture enemyPicTX;
    sf::Sprite enemyPicSP;
};

#endif