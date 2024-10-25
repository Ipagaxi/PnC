#ifndef PLAYERSTURN_HPP
#define PLAYERSTURN_HPP

#include <iostream>

#include "Activities/FightActivity/FightStates/FightState.hpp"
#include "System/Game.hpp"
#include "System/GameUI.hpp"
#include "Global/Color.hpp"
#include "Global/GenerateColorIMG.hpp"
#include "Activities/FightActivity/FightStateEnum.hpp"
#include "Global/Utility.hpp"
#include "Activities/FightActivity/FightActivityUI.hpp"

enum PlayerPhase {
  PICK_COLOR,
  ANIMATE_ATTACK,
  CHANGE_COLOR,
  END_TURN
};

class PlayersTurn: public FightState {
  public:
    PlayersTurn();
    ~PlayersTurn();
    FightStateEnum run() override;

  private:
    PlayerPhase playerPhase = PlayerPhase::PICK_COLOR;
    bool colorPicked = false;
    sf::Vector2f clickedPos;
    sf::Image oldColorImage;
    sf::Image newColorImage;
    bool newColorImageSet = false;
    float passedMillSec = 0.0;

    void processAttack();
    void changeColoPickerImage();
    double computeCurrentPixel(double formerPixel, double newPixel, float elapsedRatio);

    // Compute damage multiplier
    float mapInInterval(float value);
    float calculateSingleMultPart(Color color);
    float calculateAttackMult();

    float sameColorMetric(Color color);
    float counterColorMetric(Color color);
    float tugOfWarMetric(Color color);
};

#endif