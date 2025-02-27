//

#include "include/Game.h"
#include "include/Player.h"
#include "include/Scoreboard.h"

//
// Created by Friedrich Tröscher on 26.02.25.
Game::Game() {};

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
