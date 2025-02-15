//

#include "include/Combatant.h"
#include "include/Projectile.h"

//
// Created by Friedrich Tröscher on 15.02.25.

Combatant::Combatant(sf::Vector2f size, sf::Vector2f position, MovementBounds movementBounds, float walkingSpeed,
                     sf::Color color, float health, std::vector<Projectile> &projectiles)
        : MovementBounds(movementBounds) {

    setSize(size);
    setPosition(position);
    setFillColor(color);
    setHealth(health);
    setWalkingSpeed(walkingSpeed);
    this->projectiles = projectiles;
}

float Combatant::getHealth() {
    return health;
}

int Combatant::getReloadTime() {
    return reloadTime;
}

Direction Combatant::getDirection() {
    return direction;
}

void Combatant::setHealth(float value) {
    this->health = value;
}

void Combatant::setReloadTime(int value) {
    this->reloadTime = value;
}

void Combatant::shoot(sf::Vector2f projectileSize, int timeout, sf::Color color, float speed, int reloadTime) {
    //don't shoot if Combatant is reloading
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
                                        Projectile::generateVelocity(getDirection(), speed), timeout));

    this->projectiles.push_back(projectile);

    setLastReloadLength(reloadTime);
    setReloadTime(reloadTime);
}

void Combatant::setDirection(Direction value) {
    this->direction = value;
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
        case Direction::NONE:
            break;
    }
}

void Combatant::draw(sf::RenderWindow &window) {
    //draw the player
    window.draw(*this);
}

void Combatant::setLastReloadLength(int value) {
    this->lastReloadLength = value;
}

int Combatant::getLastReloadLength() {
    return lastReloadLength;
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
