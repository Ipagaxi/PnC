#ifndef UICOLORBOX_HPP
#define UICOLORBOX_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "UIElements/UIElement.hpp"
#include "Defines.hpp"

class UIColorBox: public UIElement {
  private:
    sf::Texture colorTX;
    sf::Texture borderTX;
    sf::Sprite colorSP;
    sf::Sprite borderSP;
    sf::Image colorBoxIMG;

  public:
    UIColorBox(std::string imagePath, std::string borderPath);

    void draw(sf::RenderWindow &window) override;
    void setPosition(float x, float y);
    sf::Vector2u getSize();
};

#endif