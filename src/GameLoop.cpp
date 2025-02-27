//
// Created by Friedrich Tröscher on 19.02.25.
//

#include "include/GameLoop.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <random>
#include "include/Player.h"
#include "include/Combatant.h"
#include "include/Scoreboard.h"
#include "include/Projectile.h"
#include "include/Monster.h"
#include "include/Game.h"

void GameLoop::run() {
    //window initialization
    auto window = sf::RenderWindow(sf::VideoMode({1280u, 720u}), "Rectangular Rampage");
    window.setFramerateLimit(60);

    //initialize game
    Game *game = new Game();

    game->player = Player({10, 10}, {10, 10}, MovementBounds({0, 0},
                                                             {1280, 648}),
                          3.f, sf::Color::White, 100, 1, 120, 1, game);
    game->scoreboard.setPosition({0, 648});

    game->monsters[0] = Monster({10, 10}, {float((rand() % window.getSize().x)), float((rand() % window.getSize().y))},
                                MovementBounds({0, 0},
                                               {1280, 648}),
                                (0.5 + (rand() % 100) / 400.f), sf::Color::Green, 100, 1, 120, game);

    for (int i = 0; i < 10; i++) {
        game->monsters.push_back(
                Monster({10, 10}, {float((rand() % window.getSize().x)), float((rand() % window.getSize().y))},
                        MovementBounds({0, 0},
                                       {1280, 648}),
                        (0.5 + (rand() % 100) / 400.f), sf::Color::Green, 100, 1, 120, game));
        //to make monsters not shoot all at the same time, they are initialized with a randomized initial reload time
        game->monsters[i].setRemainingReloadTime(rand() % game->monsters[i].getTotalReloadTime());
    }

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
        for (auto &projectile: game->projectiles) {
            auto new_end = std::remove_if(game->projectiles.begin(), game->projectiles.end(),
                                          [](Projectile projectile) {
                                              if (projectile.getTimeout() <= 0) {
                                                  return true;
                                              }
                                              return false;
                                          });
            game->projectiles.erase(new_end, game->projectiles.end());


            projectile.setTimeout(projectile.getTimeout() - 1);

            projectile.move(projectile.getVelocity());
            window.draw(projectile);
        }

        //Movement, shooting update for targetedPlayer
        game->player.tick();
        game->player.draw(window);

        //scoreboard handling
        game->scoreboard.update(game->player);
        game->scoreboard.draw(window);

        //Handle monster vector
        for (auto &monster: game->monsters) {
            monster.tick();
            monster.draw(window);
        }


        //debug point when pressing i
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) {

        }

        window.display();
    }
}
