//
// Created by Friedrich Tröscher on 05.02.25.
//

#include "include/Projectile.h"
#include <cmath>

Projectile::Projectile(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Vector2f velocity,
                       int timeout,
                       Combatant::Type shotBy, float damage,
                       Game *game) {
    setSize(size);
    setPosition(position);
    setFillColor(color);
    setVelocity(velocity);
    setTimeout(timeout);
    setGame(game);
    setShotBy(shotBy);
    setDamage(damage);
}

sf::Vector2f Projectile::getVelocity() {
    return this->velocity;
}

void Projectile::setVelocity(sf::Vector2f value) {
    velocity = value;
}

int Projectile::getTimeout() {
    return this->timeout;
}

void Projectile::setTimeout(int value) {
    timeout = value;
}

sf::Vector2f Projectile::generateFixedDirectionVelocity(Direction direction, float speed) {
    auto sqrt2 = float(sqrt(2));
    switch (direction) {
        case Direction::UP:
            return {0, -speed};
        case Direction::UP_RIGHT:
            return {speed / sqrt2, -speed / sqrt2};
        case Direction::RIGHT:
            return {speed, 0};
        case Direction::DOWN_RIGHT:
            return {speed / sqrt2, speed / sqrt2};
        case Direction::DOWN:
            return {0, speed};
        case Direction::DOWN_LEFT:
            return {-speed / sqrt2, speed / sqrt2};
        case Direction::LEFT:
            return {-speed, 0};
        case Direction::UP_LEFT:
            return {-speed / sqrt2, -speed / sqrt2};
        case Direction::NONE:
            return {0, 0};
    }
}

Combatant::Type Projectile::getShotBy() {
    return shotBy;
}

void Projectile::setShotBy(Combatant::Type value) {
    shotBy = value;
}

float Projectile::getDamage() const {
    return damage;
}

void Projectile::setDamage(float value) {
    if (damage >= 0) {
        damage = value;
    } else {
        damage = 0.f;
    }
}

Game *Projectile::getGame() const {
    return game;
}

void Projectile::setGame(Game *pointer) {
    game = pointer;
}
