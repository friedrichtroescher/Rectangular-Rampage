#include <SFML/Graphics.hpp>
#include <algorithm>
#include "include/Player.h"

int main() {
    //window initialization
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(60);


    Player player({10, 10}, {960, 540}, sf::Color::White, 100, 0);


    while (window.isOpen()) {
        // Standard SFML event loop
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // initialize a new Frame
        window.clear(sf::Color::Black);


        // Draw here

        //Movement, Shooting etc update for player
        player.tick();

        player.draw(window);

        window.display();
    }
}
