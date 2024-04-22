#ifndef INCOMINGBANNER_HPP
#define INCOMINGBANNER_HPP

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.hpp"

class IncomingBanner {
    public:
        IncomingBanner(Game &game);
        IncomingBanner(Game &game, std::string label);

        void setNewLabel(std::string newLabel);
        bool runAnimation(Game &game);
        void drawAnimation(sf::RenderWindow* gameWindow);

    private:
        sf::RectangleShape banner;
        sf::Text bannerText;
        void init(Game &game);
};

#endif