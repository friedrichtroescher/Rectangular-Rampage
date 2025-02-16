//
// Created by Friedrich Tröscher on 08.02.25.
//

#include "include/Player.h"
#include "include/Input.h"
#include "include/MovementBounds.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Player::Player(sf::Vector2f size, sf::Vector2f position, MovementBounds movementBounds, float walkingSpeed,
               sf::Color color, float health, float damage, int totalReloadTime, int level,
               std::vector<Projectile> &projectiles)
        : Combatant(size, position, movementBounds,
                    walkingSpeed, color, health, damage, totalReloadTime,
                    projectiles) {
    setLevel(level);
}

void Player::tick() {
    //update player shooting timeout and animation
    if (remainingReloadTime > 0) {
        remainingReloadTime--;
        auto reloadingColor = sf::Color(
                sf::Color(255, 255 - (float(remainingReloadTime) / float(totalReloadTime)) * 255.f,
                          255 - (float(remainingReloadTime) / float(totalReloadTime)) * 255.f, 255));
        setFillColor(reloadingColor);
    } else {
        setFillColor(sf::Color::White);
    }

    //update player position
    if (Input::getWASDDirection() != Direction::NONE) {
        walk(Input::getWASDDirection(), getWalkingSpeed());
    }

    //shooting
    if (Input::isShooting()) {
        shoot({4, 4}, 60, sf::Color::Red, 2 * 3);
    }

}

int Player::getLevel() const {
    return level;
}

void Player::setLevel(int value) {
    this->level = value;
}


