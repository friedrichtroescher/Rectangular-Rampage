#include <SFML/Graphics.hpp>
#include <algorithm>
#include <random>
#include "include/Player.h"
#include "include/Combatant.h"
#include "include/Scoreboard.h"
#include "include/Projectile.h"
#include "include/Monster.h"


int main() {
    //window initialization
    auto window = sf::RenderWindow(sf::VideoMode({1280u, 720u}), "Rectangular Rampage");
    window.setFramerateLimit(60);

    std::vector<Projectile> projectiles;

    Player player({10, 10}, {10, 10}, MovementBounds({0, 0},
                                                     {1280, 648}),
                  3.f, sf::Color::White, 100, 1, 120, 1,
                  projectiles);

    std::vector<Monster> monsters;
    for (int i = 0; i < 10; i++) {
        monsters.push_back(Monster({10, 10}, {float((rand() % 1280)), float((rand() % 648))},
                                   MovementBounds({0, 0},
                                                  {1280, 648}),
                                   (0.5 + (rand() % 100) / 400.f), sf::Color::Green, 100, 1, 120, projectiles, player));
        //to make monsters not shoot all at the same time, they are initialized with a randomized initial reload time
        monsters[i].setRemainingReloadTime(rand() % monsters[i].getTotalReloadTime());
    }


    Scoreboard scoreboard(0, 0);
    scoreboard.setPosition({0, 648});


    while (window.isOpen()) {
        // Standard SFML event loop
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // initialize a new Frame
        window.clear(sf::Color::Black);


        // update projectiles
        for (auto &projectile: projectiles) {
            auto new_end = std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile projectile) {
                if (projectile.getTimeout() <= 0) {
                    return true;
                }
                return false;
            });
            projectiles.erase(new_end, projectiles.end());


            projectile.setTimeout(projectile.getTimeout() - 1);

            projectile.move(projectile.getVelocity());
            window.draw(projectile);
        }

        //Movement, shooting update for targetedPlayer
        player.tick();
        player.draw(window);

        //scoreboard handling
        scoreboard.update(player);
        scoreboard.draw(window);

        //Handle monster vector
        for (auto &monster: monsters) {
            monster.tick();
            monster.draw(window);
        }


        //debug point when pressing i
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) {

        }

        window.display();
    }
}
