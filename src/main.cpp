#include <SFML/Graphics.hpp>
#include <algorithm>
#include "include/Player.h"

#define WALKINGSPEED 3

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

        //update projectiles
        player.tick();

        //Walking movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            player.walk(Direction::RIGHT, WALKINGSPEED);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            player.walk(Direction::LEFT, WALKINGSPEED);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            player.walk(Direction::UP, WALKINGSPEED);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            player.walk(Direction::DOWN, WALKINGSPEED);
        }

        //Shooting mechanics
        if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key::Space))) {
            player.shoot({4, 4}, 60, sf::Color::Red, 2 * WALKINGSPEED, 30);
        }

        player.draw(window);

        window.display();
    }
}
