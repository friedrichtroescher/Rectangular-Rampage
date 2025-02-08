//
// Created by Friedrich Tröscher on 05.02.25.
//

#include "include/Projectile.h"

Projectile::Projectile(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Vector2f velocity,
                       int timeout) {
    setSize(size);
    setPosition(position);
    setFillColor(color);
    setVelocity(velocity);
    setTimeout(timeout);
}

sf::Vector2f Projectile::getVelocity() {
    return this->velocity;
}

void Projectile::setVelocity(sf::Vector2f velocity) {
    this->velocity = velocity;
}

int Projectile::getTimeout() {
    return this->timeout;
}

void Projectile::setTimeout(int timeout) {
    this->timeout = timeout;
}

sf::Vector2f Projectile::generateVelocity(Direction direction, float speed) {
    switch (direction) {
        case Direction::UP:
            return {0, -speed};
        case Direction::UP_RIGHT:
            return {speed, -speed};
        case Direction::RIGHT:
            return {speed, 0};
        case Direction::DOWN_RIGHT:
            return {speed, speed};
        case Direction::DOWN:
            return {0, speed};
        case Direction::DOWN_LEFT:
            return {-speed, speed};
        case Direction::LEFT:
            return {-speed, 0};
        case Direction::UP_LEFT:
            return {-speed, -speed};
    }
}
