#include "UIElements/UIColorBox.hpp"

UIColorBox::UIColorBox(std::string imagePath, std::string borderPath) {
    this->colorTX.loadFromFile(RESOURCE_PATH "color_textures/" + imagePath);
    this->colorSP.setTexture(this->colorTX);
    this->borderTX.loadFromFile(RESOURCE_PATH "borders/" + borderPath);
    this->borderSP.setTexture(this->borderTX);

    sf::FloatRect colorRect = this->colorSP.getGlobalBounds();
    this->colorSP.setOrigin(colorRect.width/2, colorRect.height/2);

    // For a save small overlap
    this->borderSP.scale(0.97, 0.97);

    this->colorBoxIMG.loadFromFile(RESOURCE_PATH "color_textures/" + imagePath);
}

UIColorBox::UIColorBox(sf::Image image, std::string borderPath) {
    this->colorTX.loadFromImage(image);
    this->colorSP.setTexture(this->colorTX);

    this->borderTX.loadFromFile(RESOURCE_PATH "borders/" + borderPath);
    this->borderSP.setTexture(this->borderTX);

    sf::FloatRect colorRect = this->colorSP.getGlobalBounds();
    this->colorSP.setOrigin(colorRect.width/2, colorRect.height/2);

    // For a save small overlap
    this->borderSP.scale(0.97, 0.97);

    this->colorBoxIMG = image;
}

void UIColorBox::draw(sf::RenderWindow &window) {
    window.draw(this->colorSP);
    window.draw(this->borderSP);
}

void UIColorBox::setPosition(float x, float y) {
    this->borderSP.setPosition(x, y);
    sf::FloatRect borderSize = this->getSize();
    this->colorSP.setPosition(x + (borderSize.width/2), y + (borderSize.height/2));
}

sf::Vector2f UIColorBox::getPosition() {
    return this->borderSP.getPosition();
}

sf::FloatRect UIColorBox::getSize() {
    return this->borderSP.getGlobalBounds();
}

void UIColorBox::scale(float x, float y) {
    this->borderSP.scale(sf::Vector2f(x, y));
    this->colorSP.scale(sf::Vector2f(x, y));
}

sf::Color UIColorBox::getPixelColor(sf::Vector2f pos) {
    sf::FloatRect colorRect = this->colorSP.getGlobalBounds();
    sf::Vector2f offset = this->colorSP.getPosition() - sf::Vector2f(colorRect.width/2, colorRect.height/2);
    sf::Vector2f scale = this->colorSP.getScale();
    sf::Vector2f posImg = (pos - offset);
    posImg.x /= scale.x;
    posImg.y /= scale.y;
    return this->colorBoxIMG.getPixel(posImg.x, posImg.y);
}

bool UIColorBox::clickListener(GameState &gameState, sf::Vector2f &clickedPos) {
    if (gameState.mousePressed && this->colorSP.getGlobalBounds().contains(gameState.pressedPos)) {
        this->pressed = true;
    } else if (gameState.mousePressed){
        this->pressed = false;
    }
    if (this->pressed) {
        if (gameState.mouseReleased) {
            this->pressed = false;
            if (this->colorSP.getGlobalBounds().contains(gameState.releasedPos)) {
                clickedPos = sf::Vector2f(gameState.releasedPos.x, gameState.releasedPos.y);
                return true;
            }
        }
    }
    clickedPos = sf::Vector2f(0., 0.);
    return false;
}

void UIColorBox::setColorBox(std::string picPath, std::string borderPath) {
    this->colorTX.loadFromFile(RESOURCE_PATH "color_textures/" + picPath);
    this->borderTX.loadFromFile(RESOURCE_PATH "borders/" + borderPath);
}