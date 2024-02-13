#include "Activities/MenuActivity.hpp"

MenuActivity::MenuActivity() {
    this->backgroundTX.loadFromFile(RESOURCE_PATH "backgrounds/menuBG.png");
    this->backgroundSP.setTexture(this->backgroundTX);
}

void MenuActivity::executeActivity(GameState &gameState) {
    sf::RenderWindow *window = gameState.gameWindow;
    sf::Vector2u windowSize = window->getSize();
    sf::Vector2u buttonSize = this->button.basicTX.getSize();

    window->draw(this->backgroundSP);

    this->button.buttonSP.setPosition((windowSize.x - buttonSize.x)/2, (windowSize.y - buttonSize.y)/2);
    window->draw(this->button.buttonSP);

    if (button.clicked(gameState)) {
        std::unique_ptr<FightActivity> fight = std::make_unique<FightActivity>();
        gameState.setCurrentActivity(std::move(fight));
    }
}