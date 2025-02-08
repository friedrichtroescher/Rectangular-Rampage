//
// Created by Friedrich Tröscher on 08.02.25.
//

#include "include/Player.h"
#include "include/Input.h"
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
        sf::Color reloadingColor = sf::Color(
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
        walk(Input::getWASDDirection(), 3);
    }

    //shooting
    if (Input::isShooting()) {
        shoot({4, 4}, 60, sf::Color::Red, 2 * 3, 30);
    }

}

void Player::walk(Direction direction, float distance) {
    //set the direction field for later use, e.g. for shooting (or maybe a direction indicator?)
    this->setDirection(direction);

    //move the player in the given direction
    switch (direction) {
        case Direction::UP:
            move({0, -distance});
            break;
        case Direction::UP_RIGHT:
            move({distance, -distance});
            break;
        case Direction::RIGHT:
            move({distance, 0});
            break;
        case Direction::DOWN_RIGHT:
            move({distance, distance});
            break;
        case Direction::DOWN:
            move({0, distance});
            break;
        case Direction::DOWN_LEFT:
            move({-distance, distance});
            break;
        case Direction::LEFT:
            move({-distance, 0});
            break;
        case Direction::UP_LEFT:
            move({-distance, -distance});
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


