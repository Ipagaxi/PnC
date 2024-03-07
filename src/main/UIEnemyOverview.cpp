#include "UIEnemyOverview.hpp"

UIEnemyOverview::UIEnemyOverview(GameState &gameState, Enemy enemy): statsComponent(gameState, enemy), creature(enemy), creatureFrame("monster_landscape_cut/" + enemy.picPath, "actor_borders/fight_border.png") {
    sf::Vector2u windowSize = gameState.gameWindow->getSize();

    sf::FloatRect boxRect = this->backgroundBox.getSize();
    this->backgroundBox.setPosition(windowSize.x * 0.52, (windowSize.y-boxRect.height) * 0.5);
    
    float relativeOuterPaddingStatBoxes = 0.05;
    sf::FloatRect statsBoxSize = this->statsComponent.getSize();
    this->statsComponent.setPosition(windowSize.x * (1.0 - relativeOuterPaddingStatBoxes) - statsBoxSize.width, windowSize.y * 0.35);

    this->colorPicker.setColorBox(this->creature.colorPicPath, this->creature.colorPicBorderPath);
    this->colorPicker.setPosition(windowSize.x * 0.6, windowSize.y * 0.35);
    this->colorPicker.scale(0.6, 0.6);

    sf::Vector2f colorPickerPos = this->colorPicker.getPosition();
    sf::FloatRect colorPickerSize = this->colorPicker.getSize();
    sf::FloatRect creatureFrameRect = this->creatureFrame.getSize();
    float creatureBoxScale = (windowSize.x*0.22)/creatureFrameRect.width;
    this->creatureFrame.scale(creatureBoxScale, creatureBoxScale);
    creatureFrameRect = this->creatureFrame.getSize();
    this->creatureFrame.setPosition(colorPickerPos.x + colorPickerSize.width*0.5 - creatureFrameRect.width/2.f, windowSize.y * 0.11);

    sf::Vector2f creatureFramePos = this->creatureFrame.getPosition();
    this->creatureBackgroundTX.loadFromFile(RESOURCE_PATH "actor_landscape_backgrounds/forest.png");
    this->creatureBackgroundSP.setTexture(this->creatureBackgroundTX);
    sf::FloatRect creatureBackgroundRect = this->creatureBackgroundSP.getGlobalBounds();
    this->creatureBackgroundSP.setOrigin(creatureBackgroundRect.width/2.f, creatureBackgroundRect.height/2.f);
    this->creatureBackgroundSP.setPosition(creatureFramePos.x + creatureFrameRect.width/2.f, creatureFramePos.y + creatureFrameRect.height/2.f);
    this->creatureBackgroundSP.scale(creatureBoxScale, creatureBoxScale);
}

void UIEnemyOverview::draw(sf::RenderWindow &gameWindow) {
    this->backgroundBox.draw(gameWindow);
    this->statsComponent.draw(gameWindow);
    this->colorPicker.draw(gameWindow);
    gameWindow.draw(this->creatureBackgroundSP);
    this->creatureFrame.draw(gameWindow);
}

void UIEnemyOverview::changeHealth(int value) {
    int newHealth = std::max(this->creature.health - value, 0);
    this->creature.health = newHealth;
    this->statsComponent.updateHealth(newHealth);
}