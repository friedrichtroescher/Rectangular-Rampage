//
// Created by Friedrich Tröscher on 08.02.25.
//

#include "include/Player.h"
#include <SFML/Graphics.hpp>


Player::Player(sf::Vector2f size, sf::Vector2f position, sf::Color color, int health, int reloadTime) {
    setSize(size);
    setPosition(position);
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

sf::Vector2f Player::getProjectileVelocity(float speed) {
    switch (getDirection()) {
        case Direction::RIGHT:
            return {speed, 0};
        case Direction::LEFT:
            return {-speed, 0};
        case Direction::UP:
            return {0, -speed};
        case Direction::DOWN:
            return {0, speed};
    }

};

void Player::shoot(sf::Vector2f projectileSize, int timeout, sf::Color color, float speed) {
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
                                        this->getProjectileVelocity(speed), timeout));

    projectiles.push_back(projectile);

    this->setReloadTime(30);
}

void Player::tick() {
    //update player shooting timeout
    if (getReloadTime() > 0) {
        setReloadTime(getReloadTime() - 1);
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
}

void Player::walk(Direction direction, float distance) {
    //set the direction field for later use
    this->setDirection(direction);

    //move the player in the given direction
    switch (direction) {
        case Direction::RIGHT:
            move({distance, 0});
            break;
        case Direction::LEFT:
            move({-distance, 0});
            break;
        case Direction::UP:
            move({0, -distance});
            break;
        case Direction::DOWN:
            move({0, distance});
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
