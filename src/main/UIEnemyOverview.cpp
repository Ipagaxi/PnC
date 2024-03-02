#include "UIEnemyOverview.hpp"

UIEnemyOverview::UIEnemyOverview(GameState &gameState, Enemy enemy): statsComponent(gameState, enemy), creature(enemy), creatureFrame("monster_landscape_cut/" + enemy.picPath, "actor_borders/fight_border.png") {
    sf::Vector2u windowSize = gameState.gameWindow->getSize();
    float relativeOuterPaddingStatBoxes = 0.02;
    sf::FloatRect statsBoxSize = this->statsComponent.getSize();
    this->statsComponent.setPosition(windowSize.x * (1.0 - relativeOuterPaddingStatBoxes) - statsBoxSize.width, ((windowSize.y - this->statsComponent.getSize().height)/2));

    this->colorPicker.setColorBox(this->creature.colorPicPath, this->creature.colorPicBorderPath);
    this->colorPicker.setPosition(windowSize.x * 0.6, windowSize.y * 0.35);
    this->colorPicker.scale(0.6, 0.6);

    this->creatureFrame.scale(0.5, 0.5);
    sf::FloatRect creatureFrameRect = this->creatureFrame.getSize();
    //this->creatureFrame.setOrigin(creatureFrameRect.width/2.f, 0);
    sf::Vector2f colorPickerPos = this->colorPicker.getPosition();
    sf::FloatRect colorPickerSize = this->colorPicker.getSize();
    this->creatureFrame.setPosition(colorPickerPos.x + colorPickerSize.width*0.5 - creatureFrameRect.width/2.f, windowSize.y * 0.18);

    sf::Vector2f creatureFramePos = this->creatureFrame.getPosition();
    this->creatureBackgroundTX.loadFromFile(RESOURCE_PATH "actor_landscape_backgrounds/forest.png");
    this->creatureBackgroundSP.setTexture(this->creatureBackgroundTX);
    sf::FloatRect creatureBackgroundRect = this->creatureBackgroundSP.getGlobalBounds();
    this->creatureBackgroundSP.setOrigin(creatureBackgroundRect.width/2.f, creatureBackgroundRect.height/2.f);
    this->creatureBackgroundSP.setPosition(creatureFramePos.x + creatureFrameRect.width/2.f, creatureFramePos.y + creatureFrameRect.height/2.f);
    this->creatureBackgroundSP.scale(0.5, 0.5);
}

void UIEnemyOverview::draw(sf::RenderWindow &gameWindow) {
    this->statsComponent.draw(gameWindow);
    this->colorPicker.draw(gameWindow);
    gameWindow.draw(this->creatureBackgroundSP);
    this->creatureFrame.draw(gameWindow);
    //gameWindow.draw(this->creatureSP);
}

void UIEnemyOverview::changeHealth(int value) {
    int newHealth = std::max(this->creature.health - value, 0);
    this->creature.health = newHealth;
    this->statsComponent.updateHealth(newHealth);
}