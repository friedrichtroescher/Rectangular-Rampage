//

#include "include/Game.h"
#include "include/Player.h"
#include "include/Scoreboard.h"

//
// Created by Friedrich Tröscher on 26.02.25.
Game::Game() {
    gameOver = false;
};

std::vector<Projectile> &Game::getProjectiles() {
    return projectiles;
}

std::vector<Monster> &Game::getMonsters() {
    return monsters;
}

Player &Game::getPlayer() {
    return player;
}

Scoreboard &Game::getScoreboard() {
    return scoreboard;
}

void Game::setPlayer(const Player &player) {
    Game::player = player;
}

void Game::setProjectiles(const std::vector<Projectile> &projectiles) {
    Game::projectiles = projectiles;
}

void Game::setMonsters(const std::vector<Monster> &monsters) {
    Game::monsters = monsters;
}

void Game::setScoreboard(const Scoreboard &scoreboard) {
    Game::scoreboard = scoreboard;
}

std::vector<Combatant *> Game::getAllCombatants() {
    std::vector<Combatant *> combatants;
    combatants.push_back(&this->player); // Adding a pointer/reference to the actual player object
    for (auto &monster: this->getMonsters()) {
        combatants.push_back(&monster); // Adding pointers/references to actual monster objects
    }
    return combatants;
}

void Game::setGameOver() {
    gameOver = true;
}

bool Game::getGameOver() {
    return gameOver;
}

void Game::spawnMonsters(int count) {
    if (count <= 0) {
        return;
    }

    for (int i = 0; i < count; i++) {
        MovementBounds movementBounds = player.getBounds();

        monsters.push_back(
                Monster({10, 10}, {float((rand() % int(movementBounds.getBottomRightBound().x))),
                                   float((rand() % int(movementBounds.getBottomRightBound().y)))},
                        MovementBounds({0, 0},
                                       {1280, 648}),
                        (0.5 + (rand() % 100) / 400.f), sf::Color::Green, 100, 1, 120, this));
        //to make monsters not shoot all at the same time, they are initialized with a randomized initial reload time
        monsters[i].setRemainingReloadTime(rand() % monsters[i].getTotalReloadTime());
    }
}
