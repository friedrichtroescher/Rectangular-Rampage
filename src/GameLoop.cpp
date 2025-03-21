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
    auto game = std::make_unique<Game>(&window);  // Using smart pointer

    game->setPlayer(Player({10, 10}, {10, 10}, sf::RectangleShape({1280, 647}),
                           3.f, sf::Color::White, 0, 100, 0, 0, game.get()));
    game->setScoreboard(Scoreboard({0, 648}, {1280, 72}, sf::Color::Black, -5, sf::Color(50, 50, 50), game.get()));

    //loop for the game
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        if (game->getGameOver()) {
            //show the last frame until the window is closed
            continue;
        }

        // initialize a new Frame
        window.clear(sf::Color::Black);

        //initialize and update level with monsters, give player a health reload, level up and buff if all monsters are dead
        if (game->getMonsters().empty()) {
            //health reset
            game->getPlayer().setHealth(100);
            //decrease reload time by 20 for each level
            game->getPlayer().setTotalReloadTime(std::max(10, (100 - game->getPlayer().getLevel() * 20)));
            //level up
            game->getPlayer().setLevel(game->getPlayer().getLevel() + 1);
            //spawn new monsters, dependent in count on the current player level
            game->spawnMonsters(game->getPlayer().getLevel() * 2 + 3);
        }

        game->tickAndDrawProjectiles();

        //Movement, shooting update for targetedPlayer
        game->getPlayer().tick();
        window.draw(game->getPlayer());

        //no need to do a scoreboard tick, scoreboard knows about the game object and retrieves values by itself
        game->getScoreboard().draw(window);

        //handle each monster from the monster vector
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

        window.display();
    }
}
