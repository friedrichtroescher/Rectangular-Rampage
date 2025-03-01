//

#include "include/Game.h"
#include "include/Player.h"
#include "include/Scoreboard.h"

// Created by Friedrich Tröscher on 26.02.25.
Game::Game(sf::RenderWindow *renderWindow) {
    setRenderWindow(renderWindow);
    gameOver = false;
}

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

void Game::setPlayer(const Player &pointer) {
    player = pointer;
}

void Game::setProjectiles(const std::vector<Projectile> &pointer) {
    projectiles = pointer;
}

void Game::setMonsters(const std::vector<Monster> &pointer) {
    monsters = pointer;
}

void Game::setScoreboard(const Scoreboard &pointer) {
    scoreboard = pointer;
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

void Game::tickProjectiles() {
    // update projectiles
    for (auto &projectile: projectiles) {
        auto new_end = std::remove_if(projectiles.begin(), projectiles.end(),
                                      [](Projectile projectile) {
                                          if (projectile.getTimeout() <= 0) {
                                              return true;
                                          }
                                          return false;
                                      });
        projectiles.erase(new_end, projectiles.end());

        // Iterate over all combatants
        for (auto &combatant: getAllCombatants()) {
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
        getRenderWindow()->draw(projectile);
    }
}

void Game::tickMonsters() {

}

sf::RenderWindow *Game::getRenderWindow() const {
    return renderWindow;
}

void Game::setRenderWindow(sf::RenderWindow *pointer) {
    renderWindow = pointer;
}
