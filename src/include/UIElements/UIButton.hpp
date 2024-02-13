#ifndef UIBUTTON_HPP
#define UIBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "Defines.hpp"
#include "GameState.hpp"

class UIButton {
    private:
        bool hovered;
        bool pressed;

        void hoverListener(GameState &gameState);

        bool buttonContainsMouse(GameState &gameState);



    public:
        sf::Texture basicTX;
        sf::Texture clickedTX;
        sf::Texture hoveredTX;

        sf::Sprite buttonSP;

        UIButton();
        UIButton(std::string fileName, float x, float y);

        bool clicked(GameState &gameState);
};

#endif