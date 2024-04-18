#ifndef FIGHTACTIVITY_HPP
#define FIGHTACTIVITY_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <random>

#include "Activities/Activity.hpp"
#include "ActivityEnum.hpp"
#include "Animations/TextFadingManager.hpp"
#include "Animations/IncomingBanner.hpp"
#include "UIComponents/UIStats.hpp"
#include "UI_Objects/UIEnemyOverview.hpp"
#include "UI_Objects/UIPlayerOverview.hpp"
#include "UIElements/UIColorPicker.hpp"
#include "UIElements/UIButton.hpp"
#include "UIElements/UIBox.hpp"
#include "Actors/Player.hpp"
#include "PerlinNoise.hpp"
#include "Game.hpp"
#include "Defines.hpp"
#include "Actors/Enemy.hpp"
#include "Color.hpp"
#include "FightEnv.hpp"

enum FightState {

};

class FightActivity: public Activity {
  public:
    FightActivity(Game &game);
    ~FightActivity();
  
    ActivityEnum executeActivity(Game &game) override;
    void runFight(Game &game);

  private:
    FightEnv fightEnv;

    Enemy initEnemy();
    void runPlayersTurn(Game &game);
    void runEnemiesTurn(Game &game);
    void runDefeat(Game &game);
    void runVictory(Game &game);

    // Compute damage multiplier
    float mapInInterval(float value);
    float calculateSingleMultPart(Color color);
    float calculateAttackMult();
    // Metrics in file DamageMultMetrics.cpp
    float counterColorMetric(Color color);
    float tugOfWarMetric(Color color);
};

#endif