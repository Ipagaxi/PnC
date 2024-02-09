
#include "GameState.hpp"
#include "SFML/Graphics.hpp"
#include "ActivityManager.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "PnC ");

    ActivityEnum activity = Fight;
    GameState gameState = GameState(window, Fight);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        displayCurrentActivity(gameState);
        window.display();
    }
    return 0;
}