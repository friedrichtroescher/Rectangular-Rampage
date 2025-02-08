#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "include/Projectile.h"

#define playerCenter

int main() {
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(60);

    sf::RectangleShape player;
    char playerDirection = 'r';

    player.setSize({10, 10});
    player.setFillColor(sf::Color::White);

    std::vector<Projectile> projectiles;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        // Draw here

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            player.move({1, 0});
            playerDirection = 'r';
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            player.move({-1, 0});
            playerDirection = 'l';
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            player.move({0, -1});
            playerDirection = 'u';
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            player.move({0, 1});
            playerDirection = 'd';
        }

        if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key::Space))) {
            // map playerDirection to velocity
            sf::Vector2f velocity;
            switch (playerDirection) {
                case 'r':
                    velocity = {2, 0};
                    break;
                case 'l':
                    velocity = {-2, 0};
                    break;
                case 'u':
                    velocity = {0, -2};
                    break;
                case 'd':
                    velocity = {0, 2};
                    break;
            }

            Projectile projectile = (Projectile({4, 4}, {player.getPosition().x + (player.getSize().x -
                                                                                   projectile.getSize().x) /
                                                                                  2,
                                                         player.getPosition().y + (player.getSize().y -
                                                                                   projectile.getSize().y) /
                                                                                  2},
                                                sf::Color::Red,
                                                velocity, 120));

            projectiles.push_back(
                    projectile);
        }

        for (auto &projectile: projectiles) {
            auto new_end = std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile projectile) {
                return projectile.getTimeout() <= 0;
            });
            projectiles.erase(new_end, projectiles.end());


            projectile.setTimeout(projectile.getTimeout() - 1);

            projectile.move(projectile.getVelocity());

            window.draw(projectile);
        }

        window.draw(player);

        window.display();
    }
}
