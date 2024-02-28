#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Actors/Actor.hpp"
#include "UIElements/UIColorBox.hpp"
#include "Defines.hpp"

class Enemy: public Actor {
    public:
        Enemy();
        Enemy(std::string name, int health, int attackStrength, RGB defense, std::string picPath, std::string colorPicPath, std::string colorPicBorderPath);

        std::string picPath;
        std::string colorPicPath;
        std::string colorPicBorderPath;

    private:

};

#endif