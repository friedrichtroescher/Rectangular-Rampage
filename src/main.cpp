#include <SFML/Graphics.hpp>
#include <algorithm>
#include "include/Player.h"
#include "include/Scoreboard.h"

int main() {
    //window initialization
    auto window = sf::RenderWindow(sf::VideoMode({1280u, 720u}), "CMake SFML Project");
    window.setFramerateLimit(60);


    Player player({10, 10}, {10, 10}, MovementBounds({0, 0}, {1280, 648}), 3.f, sf::Color::White, 100, 0);
    Scoreboard scoreboard(100, 10);
    scoreboard.setPosition({0, 648});
    scoreboard.setSize({1280, 72});
    scoreboard.setOutlineColor(sf::Color(169, 169, 169, 255));
    scoreboard.setFillColor(sf::Color::Black);
    scoreboard.setOutlineThickness(-5);


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

        //scoreboard handling
        scoreboard.setHealth(player.getHealth());
        scoreboard.setLevel(player.getLevel());
        scoreboard.draw(window);
        window.display();
    }
}
