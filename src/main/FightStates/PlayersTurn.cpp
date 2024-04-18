#include "FightStates/PlayersTurn.hpp"

void PlayersTurn::run(Game &game, FightEnv &fightEnv) {
  switch (this->playerPhase) {
    case PlayerPhase::PICK_COLOR:
      if (fightEnv.enemyOverview.colorPicker.clickListener(game.gameEvents, this->clickedPos) && !colorPicked) {
        this->colorPicked = true;
        fightEnv.turnSP.setTexture(fightEnv.playersTurnTX);
        fightEnv.pickedColor = fightEnv.enemyOverview.colorPicker.getPixelColor(clickedPos);
        fightEnv.enemyOverview.updatePickedColorText("(" + std::to_string(fightEnv.pickedColor.r) +  ", " + std::to_string(fightEnv.pickedColor.g) + ", " + std::to_string(fightEnv.pickedColor.b) + ")", fightEnv.pickedColor);
        float attackMultiplier = this->calculateAttackMult(fightEnv);
        //std::cout << "Attack Multiplier: " << std::to_string(attackMultiplier) << std::endl;
        int damage = game.player.attackStrength * attackMultiplier;
        //std::cout << "Damage: " << damage << std::endl;
        int millSecToLive = 600;
        fightEnv.textFadingManager.startAnimation(std::to_string(damage), clickedPos, sf::Color::Yellow, game.renderEngine.gameWindow->getSize().y * 0.05, AnimationPath::Parabel, millSecToLive);
        fightEnv.enemyOverview.changeHealth(damage);
        fightEnv.newColorIMGNeeded = true;
        this->playerPhase = PlayerPhase::ANIMATE_ATTACK;
      }
      break;
    case PlayerPhase::ANIMATE_ATTACK:
      this->processAttack(fightEnv, game);
      break;
    case PlayerPhase::CHANGE_COLOR:
      break;
    case PlayerPhase::END_TURN:
      break;
  }
}

void PlayersTurn::processAttack(FightEnv &fightEnv, Game &game) {
  if (fightEnv.textFadingManager.fadingText.pastMillSec >= fightEnv.textFadingManager.fadingText.millSecToLive) {
    fightEnv.textFadingManager.fadingText.pastMillSec = 0;
    fightEnv.isPlayersTurn = (fightEnv.isPlayersTurn + 1) % 2;
    fightEnv.enemyDamageCalculated = false;
    fightEnv.turnSP.setTexture(fightEnv.enemiesTurnTX);
    fightEnv.turnChangeBanner.setNewLabel("Enemies Turn");
    this->colorPicked = false;
    fightEnv.turnIsChanging = true;
    generateTexture();
    this->playerPhase = PlayerPhase::CHANGE_COLOR;
  }
}

void PlayersTurn::changeColoPickerImage(Game &game, FightEnv &fightEnv) {
  static bool initialized = false;
  static bool newColorImageSet = false;
  static sf::Image currentColorImage = fightEnv.enemyOverview.colorPicker.colorIMG;
  static sf::Image newColorImage;
  if (!initialized) {
    newColorImage.loadFromFile(RESOURCE_PATH "color_textures/colorPIC_new.png");
    initialized = true;
  }
  sf::Uint8* pixels = new sf::Uint8[GEN_IMG_WIDTH*GEN_IMG_HEIGHT*4];
  for (int y = 0; y < GEN_IMG_HEIGHT; ++y)
  {
    for (int x = 0; x < GEN_IMG_WIDTH; ++x)
    {
      const double red = redPerlin.octave2D_01((x * fx), (y * fy), octaves, persistens) * maxColor;
      const double green = greenPerlin.octave2D_01((x * fx), (y * fy), octaves, persistens) * maxColor;
      const double blue = bluePerlin.octave2D_01((x * fx), (y * fy), octaves, persistens) * maxColor;

      int index = (y * GEN_IMG_WIDTH + x) *4;
      pixels[index] = red;
      pixels[index+1] = green;
      pixels[index+2] = blue;
      pixels[index+3] = 255;
    }
  }
  if (newColorImageSet) {
    newColorImageSet = true;
    this->playerPhase = PlayerPhase::END_TURN;
  }
}

float PlayersTurn::mapInInterval(float value) {
  return (2.f/3) * (value*value) + (1.f/3) * value;
}

// This metric rewards for picking same as defense
float PlayersTurn::sameColorMetric(Color color, FightEnv &fightEnv) {
  int pickedColorValue;
  int defenseColorValue;
  switch (color) {
    case RED:
      pickedColorValue = fightEnv.pickedColor.r;
      defenseColorValue = fightEnv.enemyOverview.creature.defense.red;
      break;
    case GREEN:
      pickedColorValue = fightEnv.pickedColor.g;
      defenseColorValue = fightEnv.enemyOverview.creature.defense.green;
      break;
    case BLUE:
      pickedColorValue = fightEnv.pickedColor.b;
      defenseColorValue = fightEnv.enemyOverview.creature.defense.blue;
      break;
    default:
      break;
  }
  int deviationFromOptimal = std::max(pickedColorValue - defenseColorValue, 0);
  float effectiveness = 1 - (deviationFromOptimal/ 250.f);
  return effectiveness;
}

//This metric rewards when hitting the exact counter colors
float PlayersTurn::counterColorMetric(Color color, FightEnv &fightEnv) {
  int pickedColorValue;
  int weakDefenseColorValue;
  switch (color) {
    case RED:
      pickedColorValue = fightEnv.pickedColor.r;
      weakDefenseColorValue = fightEnv.enemyOverview.creature.defense.green;
      break;
    case GREEN:
      pickedColorValue = fightEnv.pickedColor.g;
      weakDefenseColorValue = fightEnv.enemyOverview.creature.defense.blue;
      break;
    case BLUE:
      pickedColorValue = fightEnv.pickedColor.b;
      weakDefenseColorValue = fightEnv.enemyOverview.creature.defense.red;
      break;
    default:
      break;
  }
  int deviationFromOptimal = std::max(pickedColorValue-weakDefenseColorValue, 0);
  float effectiveness = 1 - (deviationFromOptimal/ 250.f);
  return effectiveness;
}

// This metric rewards for hitting the weak spot but punishes high colors with their counter colors
float PlayersTurn::tugOfWarMetric(Color color, FightEnv &fightEnv) {
  int pickedColorValue;
  int weakDefenseColorValue;
  int counterDefenseColorValue;
  switch (color) {
    case RED:
      pickedColorValue = fightEnv.pickedColor.r;
      weakDefenseColorValue = fightEnv.enemyOverview.creature.defense.green;
      counterDefenseColorValue = fightEnv.enemyOverview.creature.defense.blue;
      break;
    case GREEN:
      pickedColorValue = fightEnv.pickedColor.g;
      weakDefenseColorValue = fightEnv.enemyOverview.creature.defense.blue;
      counterDefenseColorValue = fightEnv.enemyOverview.creature.defense.red;
      break;
    case BLUE:
      pickedColorValue = fightEnv.pickedColor.b;
      weakDefenseColorValue = fightEnv.enemyOverview.creature.defense.red;
      counterDefenseColorValue = fightEnv.enemyOverview.creature.defense.green;
      break;
    default:
      break;
  }
  float optimalValue = std::max((2 * weakDefenseColorValue - counterDefenseColorValue) / 2.f, 0.f);
  //std::cout << "Optimal Value: " << std::to_string(optimalValue) << std::endl;
  int deviationFromOptimal = std::abs(pickedColorValue-optimalValue);
  //std::cout << "Deviation from optimal: " << std::to_string(deviationFromOptimal) << std::endl;
  float effectiveness = 1 - (deviationFromOptimal/ 250.f);
  //std::cout << "Effectiveness: " << std::to_string(effectiveness) << std::endl;
  return effectiveness;
}

float PlayersTurn::calculateSingleMultPart(Color color, FightEnv &fightEnv) {
  // Here is decided with which metric to calculated the multiplier portion
  float calulatedPortion = this->sameColorMetric(color, fightEnv);
  return mapInInterval(calulatedPortion);
}

float PlayersTurn::calculateAttackMult(FightEnv &fightEnv) {
  float redSummand = this->calculateSingleMultPart(RED, fightEnv);
  float greenSummand = this->calculateSingleMultPart(GREEN, fightEnv);
  float blueSummand = this->calculateSingleMultPart(BLUE, fightEnv);
  return (redSummand + greenSummand + blueSummand) * (fightEnv.maxMultiplier/3.f);
}