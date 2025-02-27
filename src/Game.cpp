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
