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

bool Game::getGameOver() const {
    return gameOver;
}

void Game::spawnMonsters(int count) {
    if (count <= 0) {
        return;
    }
    //monsters get smaller up until level 10, then they stay at a minimum size of 10
    float monsterSize = std::max(10.f, (15 - (float(player.getLevel()) * 0.5f)));

    for (int i = 0; i < count; i++) {
        MovementBounds movementBounds = player.getBounds();
        //the Player level is used as a multiplier in some fields to make the game harder with increasing levels
        monsters.push_back(
                Monster({monsterSize, monsterSize}, {float((rand() % int(movementBounds.getBottomRightBound().x))),
                                                     float((rand() % int(movementBounds.getBottomRightBound().y)))},
                        MovementBounds({0, 0},
                                       {1280, 648}),
                        (0.5 + (rand() % 100) / 400.f), sf::Color::Green, 100, float(player.getLevel()) * 3.f + 1.5,
                        120, this));
        //to make monsters not shoot all at the same time, they are initialized with a randomized initial reload time
        monsters[i].setRemainingReloadTime(rand() % monsters[i].getTotalReloadTime());
    }
}
