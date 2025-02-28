//
// Created by Friedrich Tröscher on 19.02.25.
//

#include "include/GameLoop.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "include/Player.h"
#include "include/Combatant.h"
#include "include/Projectile.h"
#include "include/Monster.h"
#include "include/Game.h"

void GameLoop::run() {
    //window initialization
    auto window = sf::RenderWindow(sf::VideoMode({1280u, 720u}), "Rectangular Rampage");
    window.setFramerateLimit(60);

    //initialize game
    //the whole game class is used to collect entities of the game, so that passing the game reference to those entities enables them to access other elements of the game
    Game *game = new Game();

    game->player = Player({10, 10}, {10, 10}, MovementBounds({0, 0},
                                                             {1280, 648}),
                          3.f, sf::Color::White, 0, 100, 15, 0, game);
    game->scoreboard = Scoreboard({0, 648}, {1280, 72}, sf::Color::Black, -5, sf::Color(100, 100, 100, 255), game);

    while (window.isOpen()) {
        // Standard SFML event loop
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        if (game->getGameOver()) {
            continue;
        }

        // initialize a new Frame
        window.clear(sf::Color::Black);

        //initialize and update level with monsters
        if (game->monsters.empty()) {
            game->player.setHealth(10);
            game->player.setLevel(game->player.getLevel() + 1);
            game->spawnMonsters(game->player.getLevel() * 2 + 3);
        }

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

            // Iterate over all combatants
            for (auto &combatant: game->getAllCombatants()) {
                // Check if the projectile collides with them
                if (combatant->getGlobalBounds().findIntersection(projectile.getGlobalBounds()) != std::nullopt) {
                    // Check for valid collision
                    if (projectile.getShotBy() != combatant->getType()) {
                        combatant->setHealth(combatant->getHealth() - projectile.getDamage());
                        projectile.setTimeout(0);
                    }
                }
            }


            projectile.setTimeout(projectile.getTimeout() - 1);

            projectile.move(projectile.getVelocity());
            window.draw(projectile);
        }

        //Movement, shooting update for targetedPlayer
        game->player.tick();
        window.draw(game->player);

        //no need to do a scoreboard tick, scoreboard knows about the game object and retrieves values by itself
        game->scoreboard.draw(window);

        //handle monster vector
        for (size_t index = 0; index < game->monsters.size(); /* no increment here */) {
            auto &monster = game->monsters[index];

            if (monster.getHealth() <= 0) {
                // Erase the monster and continue without incrementing index
                game->monsters.erase(game->monsters.begin() + index);
            } else {
                // Only increment the index if no erasure occurred
                monster.tick();
                window.draw(monster);
                ++index;
            }
        }


        //debug point when pressing i
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) {

        }


        window.display();
    }
}
