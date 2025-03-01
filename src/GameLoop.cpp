//
// Created by Friedrich Tröscher on 19.02.25.
//

#include "include/GameLoop.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "include/Player.h"
#include "include/Game.h"

void GameLoop::run() {
    //window initialization
    auto window = sf::RenderWindow(sf::VideoMode({1280u, 720u}), "Rectangular Rampage");
    window.setFramerateLimit(60);

    //initialize game
    //the whole game class is used to collect entities of the game, so that passing the game reference to those entities enables them to access other elements of the game
    Game *game = new Game(&window);

    game->setPlayer(Player({10, 10}, {10, 10}, sf::RectangleShape({1280, 648}),
                           3.f, sf::Color::White, 0, 100, 0, 0, game));
    game->setScoreboard(Scoreboard({0, 648}, {1280, 72}, sf::Color::Black, -5, sf::Color(50, 50, 50), game));

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

        //initialize and update level with monsters, give player a health reload, level up and buff if all monsters are dead
        if (game->getMonsters().empty()) {
            game->getPlayer().setHealth(100);
            game->getPlayer().setTotalReloadTime(std::max(10, (100 - game->getPlayer().getLevel() * 20)));
            game->getPlayer().setLevel(game->getPlayer().getLevel() + 1);
            game->spawnMonsters(game->getPlayer().getLevel() * 2 + 3);
        }

        game->tickProjectiles();

        //Movement, shooting update for targetedPlayer
        game->getPlayer().tick();
        window.draw(game->getPlayer());

        //no need to do a scoreboard tick, scoreboard knows about the game object and retrieves values by itself
        game->getScoreboard().draw(window);

        //handle monster vector
        for (size_t index = 0; index < game->getMonsters().size(); /* no increment here */) {
            auto &monster = game->getMonsters()[index];

            if (monster.getHealth() <= 0) {
                // Erase the monster and continue without incrementing index
                game->getMonsters().erase(game->getMonsters().begin() + index);
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
