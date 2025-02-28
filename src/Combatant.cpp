//

#include "include/Combatant.h"
#include "include/Projectile.h"
#include "include/Game.h"
//
// Created by Friedrich Tröscher on 15.02.25.

Combatant::Combatant(sf::Vector2f size, sf::Vector2f position, MovementBounds movementBounds, float walkingSpeed,
                     sf::Color color, float health, float damage, int totalReloadTime, Game *game)
        : MovementBounds(movementBounds) {

    setSize(size);
    setPosition(position);
    setFillColor(color);
    setHealth(health);
    setWalkingSpeed(walkingSpeed);
    setDirection(Direction::NONE);
    setDamage(damage);
    setTotalReloadTime(totalReloadTime);
    this->game = game;
}

float Combatant::getHealth() {
    return health;
}

Direction Combatant::getDirection() {
    return direction;
}

void Combatant::setHealth(float value) {
    health = value;
}


void Combatant::shoot(sf::Vector2f projectileSize, int timeout, sf::Color color, float speed) {
    if (game == nullptr) {
        return;
    }

    //don't shoot if Combatant is reloading
    if (getRemainingReloadTime() > 0) {
        return;
    }

    Projectile projectile = (Projectile(projectileSize, {getPosition().x + (getSize().x -
                                                                            projectileSize.x) /
                                                                           2.f,
                                                         getPosition().y + (getSize().y -
                                                                            projectileSize.y) /
                                                                           2.f},
                                        color,
                                        Projectile::generateFixedDirectionVelocity(getDirection(), speed),
                                        timeout, getType(), getDamage(), game));
    game->projectiles.push_back(projectile);

    //start the reload timer
    setRemainingReloadTime(getTotalReloadTime());
}

void Combatant::setDirection(Direction value) {
    direction = value;
}

void Combatant::walk(Direction direction, float distance) {
    //set the direction field for later use, e.g. for shooting (or maybe a direction indicator?)
    setDirection(direction);

    float boundDistance = this->boundDistance(direction);
    if (boundDistance < distance) {
        distance = boundDistance;
    }

    if (distance == 0) {
        return;
    }

    auto sqrt2 = float(sqrt(2)); //float precision is enough for moving these rectangles :D

    //move the targetedPlayer in the given direction
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
        case Direction::NONE:
            break;
    }
}


float Combatant::boundDistance(Direction direction) {
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
        case Direction::NONE:
            return 0;
    }
}

float Combatant::getWalkingSpeed() {
    return walkingSpeed;
}

float Combatant::setWalkingSpeed(float value) {
    walkingSpeed = value;
}

float Combatant::getDamage() {
    return damage;
}

void Combatant::setDamage(float value) {
    if (value < 0) {
        damage = 0;
    } else {
        damage = value;
    }
}

int Combatant::getTotalReloadTime() {
    return totalReloadTime;
}

int Combatant::getRemainingReloadTime() {
    return remainingReloadTime;
}

void Combatant::setTotalReloadTime(int value) {
    if (value <= 0) {
        totalReloadTime = 0;
    } else {
        totalReloadTime = value;
    }
}

void Combatant::setRemainingReloadTime(int value) {
    if (value <= 0) {
        remainingReloadTime = 0;
    } else {
        remainingReloadTime = value;
    }
}

void Combatant::shootPrecisely(sf::Vector2f projectileSize, int timeout, sf::Color color, float speed,
                               sf::Vector2f projectileMovement) {
    if (game == nullptr) {
        return;
    }

    //don't shoot if Combatant is reloading
    if (getRemainingReloadTime() > 0) {
        return;
    }

    Projectile projectile = (Projectile(projectileSize, {getPosition().x + (getSize().x -
                                                                            projectileSize.x) /
                                                                           2.f,
                                                         getPosition().y + (getSize().y -
                                                                            projectileSize.y) /
                                                                           2.f},
                                        color,
                                        projectileMovement, timeout, Combatant::Type::Monster, getDamage(), game));

    game->projectiles.push_back(projectile);

    //start the reload timer
    setRemainingReloadTime(getTotalReloadTime());
}

Combatant::Combatant() {
    setSize({10, 10});
    setPosition({0, 0});
    setFillColor(sf::Color::White);
    setHealth(100);
    setWalkingSpeed(1);
    setDirection(Direction::NONE);
    setDamage(1);
    setTotalReloadTime(1);
    setGame(nullptr);
}

Game *Combatant::getGame() const {
    return game;
}

void Combatant::setGame(Game *game) {
    Combatant::game = game;
}
