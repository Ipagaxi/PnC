#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Activity {
  public:
    virtual void displayActivity(sf::RenderWindow &window, sf::Texture &background, sf::Texture &gear);
};

#endif