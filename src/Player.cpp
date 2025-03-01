//

#include <utility>

#include "include/Player.h"
#include "include/Input.h"
#include "include/Game.h"

//
// Created by Friedrich Tröscher on 08.02.25.
Player::Player() : Combatant() {}

Player::Player(sf::Vector2f size, sf::Vector2f position, sf::RectangleShape movementBounds, float walkingSpeed,
               sf::Color color,
               float health, float damage, int totalReloadTime, int level, Game *game)
        : Combatant(size, position, std::move(movementBounds),
                    walkingSpeed, color, health, damage, totalReloadTime, game) {
    setLevel(level);
}

//the tick function takes care of every update that happens in a frame
void Player::tick() {
    if (getHealth() <= 0) {
        game->setGameOver();
    }

    //update targetedPlayer shooting timeout and animation. Similarly to Monsters, the color changes from red to white as the reload completes.
    if (remainingReloadTime > 0) {
        remainingReloadTime--;
        auto reloadingColor = sf::Color(
                sf::Color(255, 255 - (float(remainingReloadTime) / float(totalReloadTime)) * 255.f,
                          255 - (float(remainingReloadTime) / float(totalReloadTime)) * 255.f, 255));
        setFillColor(reloadingColor);
    } else {
        setFillColor(sf::Color::White);
    }

    //let the Player walk in the direction of the pressed keys
    if (Input::getWASDDirection() != Direction::NONE) {
        walk(Input::getWASDDirection(), getWalkingSpeed());
    }

    //shoot in the last walking direction if the player is pressing a shoot key
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

Combatant::Type Player::getType() {
    return Combatant::Type::Player;
}




