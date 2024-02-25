#ifndef UIBOX_HPP
#define UIBOX_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "UIElements/UIElement.hpp"
#include "Defines.hpp"

class UIBox : UIElement {
    public:
        void draw(sf::RenderWindow &window) override;
        void setPosition(float x, float y) override;
        sf::Vector2f getPosition() override;
        sf::FloatRect getSize() override;
        void scale(float x, float y) override;

        UIBox();

    private: 
        sf::RectangleShape backgroundREC;
        sf::Texture borderTX;
        sf::Sprite borderSP;

};

#endif