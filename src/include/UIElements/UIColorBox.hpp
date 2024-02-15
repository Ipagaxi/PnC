#ifndef UICOLORBOX_HPP
#define UICOLORBOX_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "UIElements/UIElement.hpp"
#include "Defines.hpp"
#include "GameState.hpp"

class UIColorBox: public UIElement {
  private:
    sf::Texture colorTX;
    sf::Texture borderTX;
    sf::Sprite colorSP;
    sf::Sprite borderSP;
    sf::Image colorBoxIMG;

    bool pressed;

  public:
    UIColorBox(std::string imagePath, std::string borderPath);

    void draw(sf::RenderWindow &window) override;
    void setPosition(float x, float y) override;
    sf::Vector2u getSize() override;

    bool clickListener(GameState &gameState, sf::Vector2f &clickedPos);

    sf::Color getPixelColor(sf::Vector2f pos);
};

#endif