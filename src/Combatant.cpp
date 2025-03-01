//

#include "include/Combatant.h"
#include "include/Projectile.h"
#include "include/Game.h"
//
// Created by Friedrich Tröscher on 15.02.25.

Combatant::Combatant(sf::Vector2f size, sf::Vector2f position, sf::RectangleShape movementBounds, float walkingSpeed,
                     sf::Color color, float health, float damage, int totalReloadTime, Game *game) {

    setSize(size);
    setPosition(position);
    setFillColor(color);
    setHealth(health);
    setWalkingSpeed(walkingSpeed);
    setDirection(Direction::NONE);
    setDamage(damage);
    setTotalReloadTime(totalReloadTime);
    setMovementBounds(movementBounds);
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
        throw std::runtime_error("Combatant has no game reference");
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
    game->getProjectiles().push_back(projectile);

    //start the reload timer
    setRemainingReloadTime(getTotalReloadTime());
}

void Combatant::setDirection(Direction value) {
    direction = value;
}

void Combatant::walk(Direction walkingDirection, float distance) {
    //set the walkingDirection field for later use, e.g. for shooting (or maybe a walkingDirection indicator?)
    setDirection(walkingDirection);

    float boundDistance = this->boundDistance(walkingDirection);
    if (boundDistance < distance) {
        distance = boundDistance;
    }

    if (distance == 0) {
        return;
    }

    auto sqrt2 = float(sqrt(2)); //float precision is enough for moving these rectangles :D

    //move the targetedPlayer in the given walkingDirection
    switch (walkingDirection) {
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


float Combatant::boundDistance(Direction boundDirectionFromCombatant) {
    sf::RectangleShape currentMovementBounds = getMovementBounds();

    auto topLeftBound = currentMovementBounds.getPoint(0);
    auto bottomRightBound = currentMovementBounds.getPoint(2);

    sf::Vector2f combatantPosition = getPosition();
    auto playerTopLeft = combatantPosition;
    auto playerTopRight = combatantPosition + sf::RectangleShape::getPoint(1);
    auto playerBottomRight = combatantPosition + sf::RectangleShape::getPoint(2);
    auto playerBottomLeft = combatantPosition + sf::RectangleShape::getPoint(3);

    switch (boundDirectionFromCombatant) {
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

void Combatant::setWalkingSpeed(float value) {
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
                               sf::Vector2f projectileDirection) {
    if (game == nullptr) {
        throw std::runtime_error("Combatant has no game reference");
    }

    //don't shoot if Combatant is reloading
    if (getRemainingReloadTime() > 0) {
        return;
    }

    //calculate the movement vector from speed and projectileDirection
    sf::Vector2f projectileVector = DirectionUtils::getNormalizedVector(projectileDirection) * speed;


    Projectile projectile = (Projectile(projectileSize, {getPosition().x + (getSize().x -
                                                                            projectileSize.x) /
                                                                           2.f,
                                                         getPosition().y + (getSize().y -
                                                                            projectileSize.y) /
                                                                           2.f},
                                        color,
                                        projectileVector, timeout, Combatant::Type::Monster, getDamage(), game));

    game->getProjectiles().push_back(projectile);

    //start the reload timer
    setRemainingReloadTime(getTotalReloadTime());
}

// default constructor is needed for the game class.
Combatant::Combatant() {
    setSize({0, 0});
    setPosition({0, 0});
    setFillColor(sf::Color::White);
    setHealth(0);
    setWalkingSpeed(0);
    setDirection(Direction::NONE);
    setDamage(0);
    setTotalReloadTime(0);
    setMovementBounds(sf::RectangleShape({0, 0}));
    setGame(nullptr);
}

[[maybe_unused]] Game *Combatant::getGame() const {
    return game;
}

void Combatant::setGame(Game *pointer) {
    game = pointer;
}

const sf::RectangleShape &Combatant::getMovementBounds() const {
    return movementBounds;
}

void Combatant::setMovementBounds(const sf::RectangleShape rectangleShape) {
    movementBounds = rectangleShape;
}
