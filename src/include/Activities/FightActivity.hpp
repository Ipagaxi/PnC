#ifndef FIGHTACTIVITY_HPP
#define FIGHTACTIVITY_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "Activities/Activity.hpp"
#include "Game.hpp"
#include "Defines.hpp"
#include "FightEnv.hpp"
#include "FightStates/PlayersTurn.hpp"
#include "FightStates/EnemiesTurn.hpp"
#include "FightStates/TurnChangeState.hpp"
#include "FightStates/FightState.hpp"
#include "FightStateEnum.hpp"

class FightActivity: public Activity {
  public:
    FightActivity();
    ~FightActivity();
  
    ActivityEnum executeActivity() override;
    void runCurrentState();

  private:
    /*
     * fightEnv is a personal current view state of FightActivity. Therefore, can not be included in Game.hpp or a derived class
    */
    FightEnv fightEnv;
    FightStateEnum currentFightStateEnum = FightStateEnum::TURN_CHANGE;
    std::shared_ptr<Enemy> enemy;

    std::unique_ptr<FightState> currentFightState;

    Enemy initEnemy();
};

#endif