//
// Created by Friedrich Tröscher on 08.02.25.
//

#include "include/Player.h"
#include "include/Input.h"
#include "include/MovementBounds.h"
#include <SFML/Graphics.hpp>
#include <cmath>


Player::Player(sf::Vector2f size, sf::Vector2f position, MovementBounds movementBounds, float walkingSpeed,
               sf::Color color, int health,
               int reloadTime) : MovementBounds(movementBounds) {
    setSize(size);
    setPosition(position);
    setWalkingSpeed(walkingSpeed);
    setFillColor(color);
    setHealth(health);
    setReloadTime(reloadTime);
}

int Player::getHealth() {
    return health;
}

int Player::getReloadTime() {
    return reloadTime;
}

Direction Player::getDirection() {
    return direction;
}

std::vector<Projectile> Player::getProjectiles() {
    return projectiles;
}

void Player::setHealth(int health) {
    this->health = health;
}

void Player::setReloadTime(int reloadTime) {
    this->reloadTime = reloadTime;
}

void Player::setDirection(Direction direction) {
    this->direction = direction;
}

void Player::setProjectiles(std::vector<Projectile> projectiles) {
    this->projectiles = projectiles;
}

void Player::shoot(sf::Vector2f projectileSize, int timeout, sf::Color color, float speed, int reloadTime) {
    //don't shoot if player is reloading
    if (getReloadTime() > 0) {
        return;
    }
    Projectile projectile = (Projectile(projectileSize, {getPosition().x + (getSize().x -
                                                                            projectileSize.x) /
                                                                           2.f,
                                                         getPosition().y + (getSize().y -
                                                                            projectileSize.y) /
                                                                           2.f},
                                        color,
                                        Projectile::generateVelocity(getDirection(), 10), timeout));

    projectiles.push_back(projectile);

    setLastReloadLength(reloadTime);
    setReloadTime(reloadTime);
}

void Player::tick() {
    //update player shooting timeout and animation
    if (getReloadTime() > 0) {
        setReloadTime(getReloadTime() - 1);
        auto reloadingColor = sf::Color(
                sf::Color(255, 255 - (float(getReloadTime()) / float(getLastReloadLength())) * 255.f,
                          255 - (float(getReloadTime()) / float(getLastReloadLength())) * 255.f, 255));
        setFillColor(reloadingColor);
    } else {
        setFillColor(sf::Color::White);
    }

    //update all projectiles
    for (auto &projectile: projectiles) {
        auto new_end = std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile projectile) {
            return projectile.getTimeout() <= 0;
        });
        projectiles.erase(new_end, projectiles.end());


        projectile.setTimeout(projectile.getTimeout() - 1);

        projectile.move(projectile.getVelocity());
    }

    //update player position
    if (Input::getWASDDirection() != Direction::NONE) {
        setDirection(Input::getWASDDirection());
        walk(Input::getWASDDirection(), getWalkingSpeed());
    }

    //shooting
    if (Input::isShooting()) {
        shoot({4, 4}, 60, sf::Color::Red, 2 * 3, 6);
    }

}

void Player::walk(Direction direction, float distance) {
    //set the direction field for later use, e.g. for shooting (or maybe a direction indicator?)
    setDirection(direction);

    //use setter here!
    float boundDistance = this->boundDistance(direction);
    if (boundDistance < distance) {
        distance = boundDistance;
    }

    if (distance == 0) {
        return;
    }

    float sqrt2 = sqrt(2);

    //move the player in the given direction
    switch (direction) {
        case Direction::UP:
            move({0, -distance});
            break;
        case Direction::UP_RIGHT:
            move({distance / sqrt2, -distance / sqrt2});
            break;
        case Direction::RIGHT:
            move({distance, 0});
            break;
        case Direction::DOWN_RIGHT:
            move({distance / sqrt2, distance / sqrt2});
            break;
        case Direction::DOWN:
            move({0, distance});
            break;
        case Direction::DOWN_LEFT:
            move({-distance / sqrt2, distance / sqrt2});
            break;
        case Direction::LEFT:
            move({-distance, 0});
            break;
        case Direction::UP_LEFT:
            move({-distance / sqrt2, -distance / sqrt2});
            break;
    }
}

void Player::draw(sf::RenderWindow &window) {
    //draw the player
    window.draw(*this);

    //draw all player projectiles
    for (auto &projectile: projectiles) {
        window.draw(projectile);
    }
}

void Player::setLastReloadLength(int lastReloadLength) {
    this->lastReloadLength = lastReloadLength;
}

int Player::getLastReloadLength() {
    return lastReloadLength;
}

float Player::boundDistance(Direction direction) {
    auto topLeftBound = getTopLeftBound();
    auto bottomRightBound = getBottomRightBound();

    auto playerTopLeft = getPosition();
    auto playerTopRight = getPosition() + sf::RectangleShape::getPoint(1);
    auto playerBottomRight = getPosition() + sf::RectangleShape::getPoint(2);
    auto playerBottomLeft = getPosition() + sf::RectangleShape::getPoint(3);

    switch (direction) {
        case Direction::UP:
            return playerTopLeft.y - topLeftBound.y;
        case Direction::UP_RIGHT:
            return std::min(playerTopRight.y - topLeftBound.y, bottomRightBound.x - playerTopRight.x);
        case Direction::RIGHT:
            return bottomRightBound.x - playerTopRight.x;
        case Direction::DOWN_RIGHT:
            return std::min(bottomRightBound.y - playerBottomRight.y, bottomRightBound.x - playerBottomRight.x);
        case Direction::DOWN:
            return bottomRightBound.y - playerBottomRight.y;
        case Direction::DOWN_LEFT:
            return std::min(bottomRightBound.y - playerBottomLeft.y, playerBottomLeft.x - topLeftBound.x);
        case Direction::LEFT:
            return playerTopLeft.x - topLeftBound.x;
        case Direction::UP_LEFT:
            return std::min(playerTopLeft.y - topLeftBound.y, playerTopLeft.x - topLeftBound.x);
    }
}

float Player::getWalkingSpeed() {
    return walkingSpeed;
}

float Player::setWalkingSpeed(float value) {
    walkingSpeed = value;
}

int Player::getLevel() {
    return level;
}

void Player::setLevel(int value) {
    this->level = value;
}


